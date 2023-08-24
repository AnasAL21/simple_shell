#include "shell.h"

/**
 * Main - Entry point
 * @Ac: Arg count
 * @Av: Arg vector
 *
 * Return: on success => 0, on error => 1
 */
int Main(int Ac, char **Av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (Ac == 2)
	{
		fd = open(Av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(Av[0]);
				_eputs(": 0: Can't open ");
				_eputs(Av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, Av);
	return (EXIT_SUCCESS);
}
