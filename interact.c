#include "shell.h"
/**
* interactive - returns true if shell is interactive mode
* @sa: struct address
**
return: 1 if interactive mode, 0 else
*/
int interactive(info_t *sa)
{
	return (isatty(STDIN_FILENO) && sa->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @cc: the character to check
 * @delimst: the delimeter string
 * return: 1 if true, 0 if false
 */
int is_delim(char cc, char *delimst)
{
	while (*delimst)
		if (*delimst++ == cc)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@cr: the character to input
 *return: 1 if cr is alphabetic, 0 else
 */

int _isalpha(int cr)
{
	if ((cr >= 'a' && cr <= 'z') || (cr >= 'A' && cr <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@stc: the string to be converted
 *return: 0 if no numbers in string,  converted number else
 */

int _atoi(char *stc)
{
	int i, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (i = 0;  stc[i] != '\0' && flag != 2; i++)
	{
		if (stc[i] == '-')
			sign *= -1;

		if (stc[i] >= '0' && stc[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (stc[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
