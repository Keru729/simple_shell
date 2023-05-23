#include "shell.h"

/**
 *_memset - fills memory with a constant byte
 *@pma: the pointer to the memory area
 *@bf: the byte to fill *pmb with
 *@abf: the amount of bytes to be filled
 *return: (pma) a pointer to the memory area pma
 */
char *_memset(char *pma, char bf, unsigned int abf)
{
	unsigned int i;

	for (i = 0; i < abf; i++)
		pma[i] = bf;
	return (pma);
}

/**
 * ffree - frees a string of strings
 * @ss: string of strings
 */
void ffree(char **ss)
{
	char **b = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(b);
}

/**
 * _realloc - reallocates a block of memory
 * @ppmb: pointer to previous malloc'ated block
 * @spb: byte size of previous block
 * @snb: byte size of new block
 *
 * return: pointer to da ol'block nameen.
 */
void *_realloc(void *ppmb, unsigned int spb, unsigned int snb)
{
	char *k;

	if (!ppmb)
		return (malloc(snb));
	if (!snb)
		return (free(ppmb), NULL);
	if (snb == spb)
		return (ppmb);

	k = malloc(snb);
	if (!k)
		return (NULL);

	snb = spb < snb ? spb : snb;
	while (spb--)
		k[spb] = ((char *)ppmb)[spb];
	free(ppmb);
	return (k);
}
