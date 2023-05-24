#include "main.h"

/**
 * get_environment - returns the string array copy of our environ
 * @info: Structure containing  arguments. 
 * Return: Always 0
 */
char **get_environment(info_all *info)
{
	if (!info->environ || info->changed_env)
	{
		info->environ = change_list_to_strings(info->env);
		info->changed_env = 0;
	}

	return (info->environ);
}

/**
 * remove_env - Remove an environment variable
 * @info: Structure containing  arguments.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int remove_env(info_all *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	for (node = info->env, i = 0; node != NULL; node = node->next, i++)
    {
        p = ch_starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->changed_env = del_index_node(&(info->env), i);
            i = 0;
            node = info->env;
        }
    }
	return (info->changed_env);
}

/**
 * init_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing  arguments.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int init_env(info_all *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node != NULL)
	{
		p = ch_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->changed_env = 1;
			return (0);
		}
		node = node->next;
	}
	node_end_add(&(info->env), buf, 0);
	free(buf);
	info->changed_env = 1;
	return (0);
}
