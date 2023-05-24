#ifndef MAIN_H
#define MAIN_H
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
#define BUF_SIZE_READ 1024
#define BUF_SIZE_WRITE 1024
#define FLUSH_BUF -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define LOWERCASE_CONVERT	1
#define UNSIGNED_CONVERT	2
#define GETLINE_USE 0
#define STRTOK_USE 0
#define FILE_HIST	".simple_shell_history"
#define MAX_HIST	4096

extern char **environ;

/**
 * struct liststrng - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststrng
{
	int numb;
	char *strng;
	struct liststrng *next;
} list_str;

/**
 * struct info_all - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @changed_env: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_str *env;
	list_str *history;
	list_str *alias;
	char **environ;
	int changed_env;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_all;

#define INIT_INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct main_builtin_table - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct
{
	char *type;
	int (*func)(info_all *);
} main_builtin_table;

char **get_environment(info_all *);
char **change_list_to_strings(list_str *);
int remove_env(info_all *, char *);
int init_env(info_all *, char *, char *);
char *ch_starts_with(const char *, const char *);
int del_index_node(list_str **, unsigned int);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
int _strlen(char *);
list_str *node_end_add(list_str **, const char *, int);
int _atoi(char *s);

#endif /* MAIN_H */
