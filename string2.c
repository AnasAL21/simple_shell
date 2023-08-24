#include "shell.h"

/**
 **_Strncat - concatenates two str
 * @Dest: The first str
 * @Src: The second str
 * @N: The amount of bytes to be max used
 * Return: The concatenated string
 */
char *_Strncat(char *Dest, char *Src, int N)
{
	int a;
	int b;
	char *s = Dest;

	a = 0;
	b = 0;
	while (Dest[a] != '\0')
		a++;
	while (Src[b] != '\0' && b < N)
	{
		Dest[a] = Src[b];
		a++;
		b++;
	}
	if (b < N)
		Dest[a] = '\0';
	return (s);
}

/**
 * _Strchr - locates a char in a string
 * @S: The string to be parsed
 * @c: The char to look for
 * Return: (s) a pointer to the memory area s
 */
char *_Strchr(char *S, char c)
{
	do {
		if (*S == c)
			return (S);
	} while (*S++ != '\0');

	return (NULL);
}
/**
 * _Strncpy - Copies a string
 * @Dest: The destination str to be copied to
 * @Src: The source str
 * @N: The amount of char to be copied
 * Return: The concatenated str
 */
char *_Strncpy(char *Dest, char *Src, int N)
{
	int a;
	int b;
	char *s = Dest;

	a = 0;
	while (Src[a] != '\0' && a < N - 1)
	{
		Dest[a] = Src[a];
		a++;
	}
	if (a < N)
	{
		b = a;
		while (b < N)
		{
			Dest[b] = '\0';
			b++;
		}
	}
	return (s);
}
