#include "shell.h"

/**
 * Fork_cmd - Forks a an exec thread to run cmd
 * @Info: The parameter & return info struct
 *
 * Return: void
 */
void Fork_cmd(info_t *Info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(Info->path, Info->argv, get_environ(Info)) == -1)
		{
			free_info(Info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(Info->status));
		if (WIFEXITED(Info->status))
		{
			Info->status = WEXITSTATUS(Info->status);
			if (Info->status == 126)
				print_error(Info, "Permission denied\n");
		}
	}
}

/**
 * Find_cmd - Finds a command in PATH
 * @Info: The parameter & return info struct
 *
 * Return: Void.
 */
void Find_cmd(info_t *Info)
{
	char *path = NULL;
	int a, b;

	Info->path = Info->argv[0];
	if (Info->linecount_flag == 1)
	{
		Info->line_count++;
		Info->linecount_flag = 0;
	}
	for (a = 0, b = 0; Info->arg[a]; a++)
		if (!is_delim(Info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(Info, _getenv(Info, "PATH="), Info->argv[0]);
	if (path)
	{
		Info->path = path;
		fork_cmd(Info);
	}
	else
	{
		if ((interactive(Info) || _getenv(Info, "PATH=")
					|| Info->argv[0][0] == '/') && is_cmd(Info, Info->argv[0]))
			fork_cmd(Info);
		else if (*(Info->arg) != '\n')
		{
			Info->status = 127;
			print_error(Info, "not found\n");
		}
	}
}

/**
 *Find_builtin - Finds a builtin command
 *@Info: the parameter & return info struct
 *
 *Return: -1 if builtin not found,
 * 0 if builtin successfully executed,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int Find_builtin(info_t *Info)
{
	int a, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(Info->argv[0], builtintbl[a].type) == 0)
		{
			Info->line_count++;
			built_in_ret = builtintbl[a].func(Info);
			break;
		}
	return (built_in_ret);
}

/**
 * Hsh - Main shell loop
 * @Info: The parameter & return info struct
 * @av: The arg vector from main()
 *
 * Return: on success put 0, on error put 1, or error code
 */
int Hsh(info_t *Info, char **av)
{
	ssize_t i = 0;
	int builtin_ret = 0;

	while (i != -1 && builtin_ret != -2)
	{
		clear_info(Info);
		if (interactive(Info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		i = get_input(Info);
		if (i != -1)
		{
			set_info(Info, av);
			builtin_ret = find_builtin(Info);
			if (builtin_ret == -1)
				find_cmd(Info);
		}
		else if (interactive(Info))
			_putchar('\n');
		free_info(Info, 0);
	}
	write_history(Info);
	free_info(Info, 1);
	if (!interactive(Info) && Info->status)
		exit(Info->status);
	if (builtin_ret == -2)
	{
		if (Info->err_num == -1)
			exit(Info->status);
		exit(Info->err_num);
	}
	return (builtin_ret);
}
