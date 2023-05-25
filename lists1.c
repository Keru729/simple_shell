#include "shell.h"

/**
 * list_len - determines length of linked list
 * @hd: pointer to first node
 *
 * return: size of list
 */
size_t list_len(const list_t *hd)
{
	size_t i = 0;

	while (hd)
	{
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @hd: pointer to first node
 *
 * return: array of strings
 */
char **list_to_strings(list_t *hd)
{
	list_t *nd = hd;
	size_t i = list_len(hd), j;
	char **sts;
	char *str;

	if (!hd || !i)
		return (NULL);
	sts = malloc(sizeof(char *) * (i + 1));
	if (!sts)
		return (NULL);
	for (i = 0; nd; nd = nd->next, i++)
	{
		str = malloc(_strlen(nd->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(sts[j]);
			free(sts);
			return (NULL);
		}

		str = _strcpy(str, nd->str);
		sts[i] = str;
	}
	sts[i] = NULL;
	return (sts);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @hd: pointer to first node
 *
 * return: size of list
 */
size_t print_list(const list_t *hd)
{
	size_t i = 0;

	while (hd)
	{
		_puts(convert_number(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @nd: pointer to list head
 * @sm: string to match
 * @ncsm: the next character after prefix to match
 *
 * return: match node or null
 */
list_t *node_starts_with(list_t *nd, char *sm, char ncsm)
{
	char *k = NULL;

	while (nd)
	{
		k = starts_with(nd->str, sm);
		if (k && ((ncsm == -1) || (*k == ncsm)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @hd: pointer to list head
 * @nd: pointer to the node
 *
 * return: index of node or -1
 */
ssize_t get_node_index(list_t *hd, list_t *nd)
{
	size_t i = 0;

	while (hd)
	{
		if (hd == nd)
			return (i);
		hd = hd->next;
		i++;
	}
	return (-1);
}
