#include "shell.h"

/**
 * _Putsfd - Prints an input str
 * @Str: The str to be printed
 * @fd: The filedescriptor to write to
 * Return: the num of chars put
 */
int _Putsfd(char *Str, int fd)
{
	int a = 0;

	if (!Str)
		return (0);
	while (*Str)
	{
		a += _putsfd(*Str++, fd);
	}
	return (a);
}

/**
 * _Putfd - Writes the char c to given fd
 * @c: The char to print
 * @fd: The filedescriptor to write to
 * Return: 1. On success
 * On error, return if it's -1, and errno is set appropriately.
 */
int _Putfd(char c, int fd)
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
 * _ePutchar - Writes the char c to stderr
 * @c: The char to print
 *
 * Return:1. On success
 * On error, return if it's -1, and errno is set appropriately.
 */
int _Eputchar(char c)
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
 * _ePuts - Prints an input str
 * @Str: the str to be printed
 *
 * Return: Void
 */
void _ePuts(char *Str)
{
	int s = 0;

	if (!Str)
		return;
	while (Str[s] != '\0')
	{
		_ePutchar(Str[s]);
		s++;
	}
}
