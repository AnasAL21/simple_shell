#include "shell.h"

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

/**
 * _putfd - Writes the char c to given fd
 * @c: The char to print
 * @fd: The filedescriptor to write to
 * Return: 1. On success
 * On error, return if it's -1, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int s;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || s >= WRITE_BUF_SIZE)
	{
		write(fd, buf, s);
		s = 0;
	}
	if (c != BUF_FLUSH)
		buf[s++] = c;
	return (1);
}

/**
 * _eputchar - Writes the char c to stderr
 * @c: The char to print
 *
 * Return:1. On success
 * On error, return if it's -1, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _eputs - Prints an input str
 * @Str: the str to be printed
 *
 * Return: Void
 */
void _eputs(char *Str)
{
	int s = 0;

	if (!Str)
		return;
	while (Str[s] != '\0')
	{
		_eputchar(Str[s]);
		s++;
	}
}
