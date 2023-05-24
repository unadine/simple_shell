#include "main.h"

/**
 * current_env - prints the current environment
 * @info: Structure containing arguments.
 * Return: Always 0
 */
int current_env(info_all *info)
{
	listStr_print(info->env);
	return (0);
}

/**
 * getting_env - gets the value of an environ variable
 * @info: Structure containing  arguments. 
 * @name: env variabe name
 *
 * Return: the value
 */
char *getting_env(info_all *info, const char *name)
{
	list_t *node;
	char *ab;

	node = info->env;
	while (node)
	{
		ab = ch_starts_with(node->str, name);
		if (ab && *ab)
			return (ab);
		node = node->next;
	}
	return (NULL);
}
/**
 * init_env - Initialize a new environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int init_env(info_all *info)
{
    int res;
    
    res = 1;
	if (info->argc == 3)
    {
        if (_settingenv(info, info->argv[1], info->argv[2]) == 0)
        {
            res = 0;
        }
    }
    else
    {
        _eputs("Incorrect number of arguments\n");
    }
    return res;
}
/**
 * remov_env - Remove an environment variable
 * @info: Structure containing  arguments.
 * Return: Always 0
 */
int remov_env(info_all *info)
{
	int ab = 1;

	if (info->argc == 1)
	{
		_eputs("Few arguments.\n");
		return (1);
	}
    while (ab < info->argc)
    {
        _unsetenv(info, info->argv[ab]);
        ab++;
    }
		
	return (0);
}

/**
 * insert_env_list - populates env linked list
 * @info: Structure containing  arguments.
 * Return: Always 0
 */
int insert_env_list(info_all *info)
{
	list_t *node = NULL;
	size_t ab;

	while (environ[ab] != NULL)
    {
        add_node_end(&node, environ[ab], 0);
        ab++;
    }
	info->env = node;
	return (0);
}
