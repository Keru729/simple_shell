#include "shell.h"
/**
* _strcpy - copies a string
* @dst: the destination
* @sr: the source
*
* return: pointer to destination
*/
char *_strcpy(char *dst, char *sr)
{
int i = 0;
if (dst == sr || sr == 0)
return (dst);
while (sr[i])
{
dst[i] = sr[i];
i++;
}
dst[i] = 0;
return (dst);
}

/**
* _stdup - duplicates a string
* @std: the string to duplicate
*
* return: pointer to the duplicated string
*/
char *_stdup(const char *std)
{
int length = 0;
char *ret;
if (std == NULL)
return (NULL);
while (*std++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--std;
return (ret);
}

/**
* _putsr - prints an input string
* @stp: the string to be printed
*
* return: Nothing
*/
void _putsr(char *stp)
{
int i = 0;
if (!stp)
return;
while (stp[i] != '\0')
{
	_putchar(stp[i]);
	i++;
}
}

/**
* _putchar - writes the character c to stdout
* @bf: The character to print
*
* return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char bf)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (bf == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (bf != BUF_FLUSH)
buf[i++] = bf;
return (1);
}
