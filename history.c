#include "shell.h"

/**
 * *get_history_file - gets the history file
 * @ps: parameter struct
 *
 * return: allocated string containg history file
 */

char *get_history_file(info_t *ps)
{
	char *buff, *dr;

	dr = _getenv(ps, "HOME=");
	if (!dr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @ps: the parameter struct
 *
 * return: 1 on success, else -1
 */
int write_history(info_t *ps)
{
	ssize_t fd;
	char *filename = get_history_file(ps);
	list_t *nd = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nd = ps->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @ps: the parameter struct
 *
 * return: histcount on success, else 0
 */
int read_history(info_t *ps)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(ps);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history_list(ps, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(ps, buff + last, linecount++);
	free(buff);
	ps->histcount = linecount;
	while (ps->histcount-- >= HIST_MAX)
		delete_node_at_index(&(ps->history), 0);
	renumber_history(ps);
	return (ps->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @pa: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecount: the history linecount, histcount
 *
 * return: always 0
 */
int build_history_list(info_t *pa, char *buff, int linecount)
{
	list_t *nd = NULL;

	if (pa->history)
		nd = pa->history;
	add_node_end(&nd, buff, linecount);

	if (!pa->history)
		pa->history = nd;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @pa: Structure containing potential arguments. Used to maintain
 *
 * return: the new histcount
 */
int renumber_history(info_t *pa)
{
	list_t *nd = pa->history;
	int i = 0;

	while (nd)
	{
		nd->num = i++;
		nd = nd->next;
	}
	return (pa->histcount = i);
}
