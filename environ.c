#include "shell.h"

/**
 * Populate_env_list - Populates env linked list
 * @Info: Struc containing potential arg. Used to maintain
 *          const function prototype.
 * Return:0 Always
 */
int Populate_env_list(info_t *Info)
{
	list_t *node = NULL;
	size_t s;

	for (s = 0; environ[s]; s++)
		add_node_end(&node, environ[s], 0);
	Info->env = node;
	return (0);
}

/**
 * _Myunsetenv - Remove an envir var
 * @Info: Structure containing potential arg. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _Myunsetenv(info_t *Info)
{
	int s;

	if (Info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (s = 1; s <= Info->argc; s++)
		_unsetenv(Info, Info->argv[s]);

	return (0);
}

/**
 *_Getenv - Gets the value of an environ var
 *@Info: Structure containing potential arg. Used to maintain
 *@Name: env var name
 *
 *Return: the value
 */
char *_Getenv(info_t *Info, const char *Name)
{
	list_t *node = Info->env;
	char *s;

	while (node)
	{
		s = starts_with(node->str, name);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * _Mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @Info: StrucT containing potential arg. Used to maintain
 *        const function prototype.
 * Return: Always 0
 */
int _Mysetenv(info_t *Info)
{
	if (Info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(Info, Info->argv[1], Info->argv[2]))
		return (0);
	return (1);
}

/**
 *_Myenv - Prints the current environM
 *@Info: Struc containing potential arg. Used to maintain
 *          const function prototype.
 *Return: Always 0
 */
int _Myenv(info_t *Info)
{
	print_list_str(Info->env);
	return (0);
}
