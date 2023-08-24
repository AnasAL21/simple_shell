#include "shell.h"

/**
 * _putchar - Writes the char c to stdout
 *@c: The char to print
 *
 * Return: 1. On success
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _strdup - Duplicates a string
 * @Str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *Str)
{
	int len = 0;
	char *ret;

	if (Str == NULL)
		return (NULL);
	while (*Str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--Str;
	return (ret);
}

/**
 * _puts - Prints an input str
 * @Str: The string to be printed
 *
 * Return: Nothing
 */
void _puts(char *Str)
{
	int a = 0;

	if (!Str)
		return;
	while (Str[a] != '\0')
	{
		_putchar(Str[a]);
		a++;
	}
}

/**
 * _strcpy - copies a string
 * @Dest: the destination
 * @Src: the source
 *
 * Return: Pointer to destination
 */
char *_strcpy(char *Dest, char *Src)
{
	int a = 0;

	if (Dest == Src || Src == 0)
		return (Dest);
	while (Src[a])
	{
		Dest[a] = Src[a];
		a++;
	}
	Dest[a] = 0;
	return (Dest);
}
