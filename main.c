#include "shell.h"

/**
* main - entry point
* @ac: arg count
* @av: arg vector
*
* return: 0 on success, 1 on error
*/
int main(int ac, char **av)
{
	info_t sa[] = { INFO_INIT };

	if (ac == 2)
	{
		sa->readfd = open_file(sa, av[1], 0);
		if (sa->readfd == -1)
		{
			free_info(sa, 1);
			exit(sa->err_num);
		}
	}
	populate_env_list(sa);
	read_history(sa);
	read_startup_file(sa);
	hsh(sa, av);
	return (EXIT_SUCCESS);
}
