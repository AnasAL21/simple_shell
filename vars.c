#include "shell.h"

/**
 * Replace_string - Replaces string
 * @Old: Address of old string
 * @new: New string
 *
 * Return: 1 if replaced, otherwise 0
 */
int Replace_string(char **Old, char *new)
{
	free(*Old);
	*Old = new;
	return (1);
}

/**
 * Replace_vars - Replaces vars in the tokenized string
 * @Info: The parameter struct
 *
 * Return: 1 if replaced, otherwise 0
 */
int Replace_vars(info_t *Info)
{
	int a = 0;
	list_t *node;

	for (a = 0; Info->argv[a]; a++)
	{
		if (Info->argv[a][0] != '$' || !Info->argv[a][1])
			continue;

		if (!_strcmp(Info->argv[a], "$?"))
		{
			Replace_string(&(Info->argv[a]),
					_strdup(convert_number(Info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(Info->argv[a], "$$"))
		{
			Replace_string(&(Info->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(Info->env, &Info->argv[a][1], '=');
		if (node)
		{
			Replace_string(&(Info->argv[a]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		Replace_string(&Info->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * Check_chain - checks we should continue chaining based on last status
 * @Info: the parameter struct
 * @Buf: the char buffer
 * @P: address of current position in buf
 * @a: starting position in buf
 * @Len: length of buf
 *
 * Return: Void
 */
void Check_chain(info_t *Info, char *Buf, size_t *P, size_t a, size_t Len)
{
	size_t b = *P;

	if (Info->cmd_buf_type == CMD_AND)
	{
		if (Info->status)
		{
			Buf[a] = 0;
			b = Len;
		}
	}
	if (Info->cmd_buf_type == CMD_OR)
	{
		if (!Info->status)
		{
			Buf[a] = 0;
			b = Len;
		}
	}

	*P = b;
}

/**
 *Replace_alias - Replaces an aliases in the tokenized string
 *@Info: the parameter struct
 *
 *Return: if replaced 1, otherwise 0
 */
int Replace_alias(info_t *Info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(Info->alias, Info->argv[0], '=');
		if (!node)
			return (0);
		free(Info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		Info->argv[0] = p;
	}
	return (1);
}

/**
 *Is_chain - Test if current character in buffer is a chain delimeter
 *@info: The parameter struct
 *@buf: The char buffer
 *@P: Address of current position in buf
 *
 *Return: if chain delimeter then 1, otherwise 0
 */
int Is_chain(info_t *info, char *buf, size_t *P)
{
	size_t a = *P;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';')
	{
		buf[a] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*P = a;
	return (1);
}

