#include "shell.h"

/**
 * _Unsetenv - Remove an environment variable
 * @Info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _Unsetenv(info_t *Info, char *var)
{
	list_t *node = Info->env;
	size_t x = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			Info->env_changed = delete_node_at_index(&(Info->env), x);
			x = 0;
			node = Info->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (Info->env_changed);
}

/**
 * _Setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @Info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _Setenv(info_t *Info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = Info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			Info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(Info->env), buf, 0);
	free(buf);
	Info->env_changed = 1;
	return (0);
}

/**
 * Get_environ - Returns the string array copy of our environ
 * @Info: Struc containing potential arguments. Used to maintain
 *          const function prototype.
 * Return: 0
 */
char **Get_environ(info_t *Info)
{
	if (!Info->environ || Info->env_changed)
	{
		Info->environ = list_to_strings(Info->env);
		Info->env_changed = 0;
	}

	return (Info->environ);
}
