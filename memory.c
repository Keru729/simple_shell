#include "shell.h"
/**
* bfree - frees a pointer and NULL  address
* @aptr: address of the pointer to free
*
* return: 1 if freed, else 0.
*/
int bfree(void **aptr)
{
if (aptr && *aptr)
{
free(*aptr);
*aptr = NULL;
return (1);
}
return (0);
}
