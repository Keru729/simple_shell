#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @hd: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * return: size of list
 */
list_t *add_node(list_t **hd, const char *str, int num)
{
list_t *new_hd;
if (!hd)
return (NULL);
new_hd = malloc(sizeof(list_t));
if (!new_hd)
return (NULL);
_memset((void *)new_hd, 0, sizeof(list_t));
new_hd->num = num;
if (str)
{
new_hd->str = _strdup(str);
if (!new_hd->str)
{
free(new_hd);
return (NULL);
}
}
new_hd->next = *hd;
*hd = new_hd;
return (new_hd);
}

/**
 * add_node_end - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * return: size of list
 */
list_t *add_node_end(list_t **hd, const char *str, int num)
{
list_t *new_nd, *nd;
if (!hd)
return (NULL);
nd = *hd;
new_nd = malloc(sizeof(list_t));
if (!new_nd)
return (NULL);
_memset((void *)new_nd, 0, sizeof(list_t));
new_nd->num = num;
if (str)
{
new_nd->str = _strdup(str);
if (!new_nd->str)
{
free(new_nd);
return (NULL);
}
}
if (nd)
{
while (nd->next)
nd = nd->next;
nd->next = new_nd;
}
else
*hd = new_nd;
return (new_nd);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @pfn: pointer to first node
 *
 * return: size of list
 */
size_t print_list_str(const list_t *pfn)
{
size_t i = 0;
while (pfn)
{
_puts(pfn->str ? pfn->str : "(nil)");
_puts("\n");
pfn = pfn->next;
i++;
}
return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @hd: address of pointer to first node
 * @index: index of node to delete
 *
 * return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **hd, unsigned int index)
{
list_t *nd, *prev_nd;
unsigned int i = 0;
if (!hd || !*hd)
return (0);
if (!index)
{
nd = *hd;
*hd = (*hd)->next;
free(nd->str);
free(nd);
return (1);
}
nd = *hd;
while (nd)
{
if (i == index)
{
prev_nd->next = nd->next;
free(nd->str);
free(nd);
return (1);
}
i++;
prev_nd = nd;
nd = nd->next;
}
return (0);
}

/**
 * free_list - frees all nodes of a list
 * @aphn: address of pointer to head node
 *
 * return: void
 */
void free_list(list_t **aphn)
{
list_t *nd, *next_nd, *hd;
if (!aphn || !*aphn)
return;
hd = *aphn;
nd = hd;
while (nd)
{
next_nd = nd->next;
free(nd->str);
free(nd);
nd = next_nd;
}
*aphn = NULL;

}
