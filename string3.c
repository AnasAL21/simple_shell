#include "shell.h"

/**
 * **Strtow - Splits a str into words. Repeat delimiters are ignored
 * @Str: The input string
 * @i: The delimeter string
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **Strtow(char *Str, char *i)
{
	int a, b, d, e;
	int Numwords = 0;
	char **s;

	if (Str == NULL || Str[0] == 0)
		return (NULL);
	if (!i)
		i = " ";
	for (a = 0; Str[a] != '\0'; a++)
		if (!is_delim(Str[a], i) && (is_delim(Str[a + 1], i) || !Str[a + 1]))
			Numwords++;

	if (Numwords == 0)
		return (NULL);
	s = malloc((1 + Numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < Numwords; b++)
	{
		while (is_delim(Str[a], i))
			a++;
		d = 0;
		while (!is_delim(Str[a + d], i) && Str[a + d])
			d++;
		s[b] = malloc((d + 1) * sizeof(char));
		if (!s[b])
		{
			for (d = 0; d < b; d++)
				free(s[d]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < b; e++)
			s[b][e] = Str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **Strtow2 - Splits a string into words
 * @Str: The input string
 * @i: The delimeter
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **Strtow2(char *Str, char i)
{
	int a, b, d, e;
	int Numwords = 0;
	char **s;

	if (Str == NULL || Str[0] == 0)
		return (NULL);
	for (a = 0; Str[a] != '\0'; a++)
		if ((Str[a] != i && Str[a + 1] == i) ||
				    (Str[a] != i && !str[a + 1]) || str[a + 1] == i)
			Numwords++;
	if (Numwords == 0)
		return (NULL);
	s = malloc((1 + Numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < Numwords; b++)
	{
		while (str[a] == i && Str[a] != i)
			a++;
		d = 0;
		while (Str[a + d] != i && Str[a + d] && str[a + d] != i)
			d++;
		s[b] = malloc((d + 1) * sizeof(char));
		if (!s[b])
		{
			for (d = 0; d < b; d++)
				free(s[d]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < d; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}

