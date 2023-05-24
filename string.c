#include "shell.h"

/**
* _strlen:  return the length of a strings
* @st: the strings whose length to check
*
* return: integer length of strings
*/
int _strlen(char *st)
{
int i = 0;
if (!st)
return (0);
while (*st++)
i++;
return (i);
}

/**
* _strcmp - performs comparison of two strangs.
* @st1: the second strang
* @st2: the first strang
*
* return: negative if st1 < st2, positive if st1 > st2, zero if st1 == st2
*/
int _strcmp(char *st1, char *st2)
{
while (*st1 && *st2)
{
if (*st1 != *st2)
return (*st1 - *st2);
st1++;
st2++;
}
if (*st1 == *st2)
return (0);
else
return (*st1 < *st2 ? -1 : 1);
}
/**
 *  starts_with - checks if sbf starts with ss
 *  @ss: string to search
 *  @sbf: the substring to find
 *
 *  return: address of next char of ss or NULL
 */
char *starts_with(const char *ss, const char *sbf)
{
while (*ss)
if (*sbf++ != *ss++)
	return (NULL);
return ((char *)ss);
}

/**
 * _strcat - concatenates two strings
 * @dsf: the destination buffer
 * @srf: the source buffer
 *
 * return: pointer to destination buffer
*/
char *_strcat(char *dsf, char *srf)
{
char *ret = dsf;
while (*dsf)
dsf++;
while (*srf)
*dsf++ = *srf++;
*dsf = *srf;
return (ret);
}
