#include "shell.h"

/**
 * _Realloc - Reallocates a block of memory
 * @Ptr: Pointer to previous malloc'ated block
 * @Old_size: Byte size of previous block
 * @New_size: Byte size of new block
 *
 * Return: pointer to that old block nameen.
 */
void *_Realloc(void *Ptr, unsigned int Old_size, unsigned int New_size)
{
	char *s;

	if (!Ptr)
		return (malloc(new_size));
	if (!New_size)
		return (free(Ptr), NULL);
	if (New_size == Old_size)
		return (Ptr);

	p = malloc(New_size);
	if (!s)
		return (NULL);

	Old_size = Old_size < New_size ? Old_size : New_size;
	while (Old_size--)
		s[Old_size] = ((char *)Ptr)[Old_size];
	free(Ptr);
	return (s);
}

/**
 * Ffree - Frees a str of strings
 * @PP: Str of strings
 */
void Ffree(char **PP)
{
	char **a = PP;

	if (!PP)
		return;
	while (*PP)
		free(*PP++);
	free(a);
}

/**
 * _Memset - fills memory with a constant byte
 * @a: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (a) a pointer to the memory area a
 */
char *_Memset(char *a, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (a);
}
