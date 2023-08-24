#include "shell.h"

/**
 * Clear_info - Initialize info_t struct
 * @Info: structure address
 */
void Clear_info(Info_t *Info)
{
	Info->arg = NULL;
	Info->argv = NULL;
	Info->path = NULL;
	Info->argc = 0;
}

/**
 * Set_info - Initialize info_t struct
 * @Info: Struct address
 * @Av: Arg vector
 */
void Set_info(info_t *Info, char **Av)
{
	int s = 0;

	Info->fname = Av[0];
	if (Info->arg)
	{
		Info->argv = strtow(Info->arg, " \t");
		if (!Info->argv)
		{
			Info->argv = malloc(sizeof(char *) * 2);
			if (Info->argv)
			{
				Info->argv[0] = _strdup(Info->arg);
				Info->argv[1] = NULL;
			}
		}
		for (s = 0; Info->argv && Info->argv[s]; s++)
			;
		Info->argc = s;

		replace_alias(Info);
		replace_vars(Info);
	}
}

/**
 * Free_info - Frees info_t structure fields
 * @Info: Struct address
 * @All: True if freeing all fields
 */
void Free_info(info_t *Info, int All)
{
	ffree(Info->argv);
	Info->argv = NULL;
	Info->path = NULL;
	if (All)
	{
		if (!Info->cmd_buf)
			free(Info->arg);
		if (Info->env)
			free_list(&(Info->env));
		if (Info->history)
			free_list(&(Info->history));
		if (Info->alias)
			free_list(&(Info->alias));
		ffree(Info->environ);
			Info->environ = NULL;
		bfree((void **)Info->cmd_buf);
		if (Info->readfd > 2)
			close(Info->readfd);
		_putchar(BUF_FLUSH);
	}
}
