#include "shell.h"

/**
 *_eputs - prints an input string
 * @stp: the string to be printed
 *
 * return: Nothing
 */
void _eputs(char *stp)
{
	int i = 0;

	if (!stp)
		return;
	while (stp[i] != '\0')
	{
		_eputchar(stp[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @cp: The character to print
 *
 * return: On success 1.
 * On error, -1 is returned, and error no is set appropriately.
 */
int _eputchar(char cp)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cp == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (cp != BUF_FLUSH)
		buf[i++] = cp;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @cp: The character to print
 * @fdw: The filedescriptor to write to
 *
 * return: On success 1.
 * On error, -1 is returned, and error no is set appropriately.
 */
int _putfd(char cp, int fdw)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cp == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fdw, buf, i);
		i = 0;
	}
	if (cp != BUF_FLUSH)
		buf[i++] = cp;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @stp: the string to be printed
 * @fdw: the filedescriptor to write to
 *
 * return: the number of characters put
 */
int _putsfd(char *stp, int fdw)
{
	int i = 0;

	if (!stp)
		return (0);
	while (*stp)
	{
		i += _putfd(*stp++, fdw);
	}
	return (i);
}
