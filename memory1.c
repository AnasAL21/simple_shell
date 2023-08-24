#include "shell.h"

/**
 *Bfree - Frees a pointer and NULLs the address.
 *@Ptr: Address of the pointer to free.
 *Return: 1 if freed, 0 otherwise.
 */
int Bfree(void **Ptr)
{
	if (Ptr && *Ptr)
	{
		free(*Ptr);
		*Ptr = NULL;
		return (1);
	}
	return (0);
}

