#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

/* for write/read buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command change */
#define CMD_PIPE 4
#define CMD_CHAIN 3
#define CMD_AND 2
#define CMD_OR  1
#define CMD_NORM 0

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK0 0

/* for convertion of numbers() */
#define CONVERT_UNSIGNED 2
#define CONVERT_LOWERCASE 1

/* 1 if using system getline() */
#define USE_STRTOK 0
#define USE_GETLINE 0
#define HIST_MAX 4096
#define HIST_FILE ".simple_shell_history"

extern char **environ;

/**
* struct liststr - singly linked list
* @str: a string
* @num: the number field
* @next: points to the next node
*/
typedef struct liststr
{
char *str;
int num;
struct liststr *next;
}
list_t;

/**
 * allowing uniform prototype for function pointer struct,
 * struct passinfo - contains pseudo-arguements to pass into a function
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @histcount: the history line number count
 * @readfd: the fd from which to read line input
*/
typedef struct passinfo
{
char *arg;
char **argv;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
char *path;
int argc;
list_t *alias;
char **environ;
list_t *env;
list_t *history;
int status;
int env_changed;

char **cmd_buf;
/* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type;
/* CMD_type ||, &&, ; */
int histcount;
int readfd;
}
info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0, -1, 0, 1, -1, 0, NULL, NULL, NULL, NULL, {0}, -1, 0, 0}

/**
* struct builtin - contains a builtin string and related function
* @type: the builtin command flag
* @func: the function
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

/* toem_parser.c */
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_string.c */
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);

/* toem_string1.c */
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);

/* toem_errors.c */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);

/* toem_exits.c */
char *_strchr(char *, char);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);

/* toem_memory.c */
int bfree(void **);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_atoi.c */
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);

/* toem_realloc.c */
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
void ffree(char **);

/* toem_errors1.c */
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(info_t *, char *);

/* toem_builtin.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);

/* toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/* toem_environ.c */
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getinfo.c */
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);

/*toem_getline.c */
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t get_input(info_t *);

/* toem_getenv.c */
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

/* toem_vars.c */
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

/* toem_lists.c */
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);

/* toem_lists1.c */
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);

#endif
