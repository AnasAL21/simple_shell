#include "shell.h"

/**
 * _Myalias - Mimics the alias builtin (man alias)
 * @Info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _Myalias(info_t *Info)
{
	int a = 0;
	char *s = NULL;
	list_t *node = NULL;

	if (Info->argc == 1)
	{
		node = Info->alias;
		while (node)
		{
			print_list(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; Info->argv[a]; a++)
	{
		s = _strchr(Info->argv[a], '=');
		if (s)
			set_alias(Info, Info->argv[a]);
		else
			print_alias(node_starts_with(Info->alias, Info->argv[a], '='));
	}

	return (0);
}

/**
 * Print_alias - Prints an alias string
 * @Node: The alias node
 *
 * Return: Always on success 0, on error 1
 */
int Print_alias(list_t *Node)
{
	char *s = NULL, *i = NULL;

	if (Node)
	{
		s = _strchr(Node->str, '=');
		for (i = node->str; i <= s; i++)
		_putchar(*i);
		_putchar('\'');
		_puts(s + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * Unset_alias - Sets alias to str
 * @Info: Parameter structure
 * @Str: the str alias
 *
 * Return: Always on success 0 , on error 1
 */
int Unset_alias(info_t *Info, char *Str)
{
	char *s, a;
	int ret;

	p = _strchr(Str, '=');
	if (!s)
		return (1);
	a = *s;
	*s = 0;
	ret = delete_node_at_index(&(Info->alias),
		get_node_index(Info->alias, node_starts_with(Info->alias, Str, -1)));
	*s = a;
	return (ret);
}

/**
 * Set_alias - Sets alias to str
 * @Info: parameter struct
 * @Str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int Set_alias(info_t *Info, char *Str)
{
	char *s;

	p = _strchr(Str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(Info, Str));

	unset_alias(info, Str);
	return (add_node_end(&(Info->alias), Str, 0) == NULL);
}

/**
 * _Myhistory - displays the history list, one command by line, preceded
 *              with line num, starting at 0.
 * @Info: Structure containing potential arg. Used to maintain
 *        const function prototype.
 *  Return: Always 0
 */
int _Myhistory(info_t *Info)
{
	print_list(Info->history);
	return (0);
}
