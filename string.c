#include "shell.h"

/**
 * _Strcat - Concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to dest buffer
 */
char *_Strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * Starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next character of haystack or NULL
 */
char *Starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _Strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 *Return: if s1 < s2 => negative, if s1 > s2 => positive, if s1 == s2 => zero
 */
int _Strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _Strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _Strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
