#include "shell.h"

/**
 * Remove_comments - function replaces first instance of '#' with '\0'
 * @Buf: address of the string to modify
 *
 * Return: Always 0;
 */
void Remove_comments(char *Buf)
{
	int s;

	for (s = 0; Buf[s] != '\0'; s++)
		if (Buf[s] == '#' && (!s || Buf[s - 1] == ' '))
		{
			Buf[s] = '\0';
			break;
		}
}

/**
 * Print_d - funct prints a decimal (integer) number (base 10)
 * @Input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
 */
int Print_d(int Input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a;
	int count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (Input < 0)
	{
		_abs_ = -Input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = Input;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			count++;
		}
		current %= a;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * Convert_number - Converter funcT, a clone of itoa
 * @Num: number
 * @Base: base
 * @Flags: argument flags
 * Return: string
 */
char *Convert_number(long int Num, int Base, int Flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = Num;

	if (!(Flags & CONVERT_UNSIGNED) && Num < 0)
	{
		n = -Num;
		sign = '-';

	}
	array = Flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % Base];
		n /= Base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * Print_error - Prints an error message
 * @Info: the parameter & return info structure
 * @Estr: str containing specified err type
 * Return: if no numbers in string then 0, converted number otherwise
 *        -1 on error
 */
void Print_error(info_t *Info, char *Estr)
{
	_eputs(Info->fname);
	_eputs(": ");
	print_d(Info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(Info->argv[0]);
	_eputs(": ");
	_eputs(Estr);
}

/**
 * _Erratoi - converts a str to an int
 * @x: The str to be converted
 * Return: if no numbers in string then 0, converted number otherwise
 *       -1 on error
 */
int _Erratoi(char *x)
{
	int a = 0;
	unsigned long int result = 0;

	if (*x == '+')
		x++;
	for (a = 0;  x[a] != '\0'; a++)
	{
		if (x[a] >= '0' && x[a] <= '9')
		{
			result *= 10;
			result += (x[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

