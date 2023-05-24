#include "shell.h"
/**
* clear_info - initializes info_t struct
* @sa: struct address
*/
void clear_info(info_t *sa)
{
sa->arg = NULL;
sa->argv = NULL;
sa->path = NULL;
sa->argc = 0;
}

/**
* set_info - initializes info_t struct
* @sa: struct address
* @av: argument vector
*/
void set_info(info_t *sa, char **av)
{
int i = 0;
sa->fname = av[0];
if (sa->arg)
{
sa->argv = strtow(sa->arg, " \t");
if (!sa->argv)
{
sa->argv = malloc(sizeof(char *) * 2);
if (sa->argv)
{
sa->argv[0] = _strdup(sa->arg);
sa->argv[1] = NULL;
}
}
for (i = 0; sa->argv && sa->argv[i]; i++)
;
sa->argc = i;
replace_alias(sa);
replace_vars(sa);
}
}

/**
* free_info - frees info_t struct fields
* @sa: struct address* @all: true if freeing all fields
*/
void free_info(info_t *sa, int all)
{
ffree(sa->argv);
sa->argv = NULL;
sa->path = NULL;
if (all)
{
if (!sa->cmd_buf)
free(sa->arg);
if (sa->env)
free_list(&(sa->env));
if (sa->history)
free_list(&(sa->history));
if (sa->alias)
free_list(&(sa->alias));
ffree(sa->environ);
sa->environ = NULL;
bfree((void **)sa->cmd_buf);
if (sa->readfd > 2)
close(sa->readfd);
_putchar(BUF_FLUSH);
}
}

