/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:29:03 by loribeir          #+#    #+#             */
/*   Updated: 2025/04/24 13:27:32 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

/**
 * @brief: export set the export attribute for variables corresponding to the
 * specified names.
 */

int    ft_export(t_shell *shell, t_cmd *cmds)
{
	char    **env_val;
	char    *value;
	t_env   *tmp;
	size_t  len;
	int     i;

	tmp = shell->env;
	i = 1;
	while (cmds->args[i])
	{
		env_val = ft_split(cmds->args[i], '=');
		if (!env_val[0] || !ft_strchr(cmds->args[i], '=') || 
			verify_args_export(cmds->args[i]) != SUCCESS)
		{
			shell->exit_status = 1;
			return (FAIL);
		}
		len = ft_strlen(env_val[0]) + 1;	
		value = ft_strdup(cmds->args[i] + len);
		update_export(tmp, env_val[0], value);
		i++;
	}
	shell->exit_status = 0;
	return (SUCCESS);
}

int verify_args_export(char *args)
{
	size_t i;
	
	i = 0;
	if (!ft_strchr(args, '='))
		return (FAIL);
	while (args[i] && args[i] != '=')
	{
		if ((!ft_isalnum(args[i]) || args[i] != '_'))
		{
			if ((args[i] == '+' && args[i + 1] != '='))
				return (ft_fdprintf(1, "bash: export: '%s': not a valid identifier\n", args), FAIL);
		}
		i++;
	}
	if (ft_isdigit(args[0]) || ft_strchr(args, '+'))
		return (ft_fdprintf(1, "bash: export: '%s': not a valid identifier\n", args), FAIL);
	if (!ft_isalpha(args[0]) && args[0] != '_')
		return (ft_fdprintf(1, "bash: export: invalid option\n"), FAIL);
	return (SUCCESS);
}

void    update_export(t_env *tmp, char *key, char *value)
{
	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value= ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	add_var_back(tmp, key, value);
}

/* export: function add variable to the env. */
t_env   *add_var_back(t_env *env, char *key, char *value)
{
    t_env   *tmp;
    t_env   *new_var;
    
    new_var = malloc(sizeof(t_env));
    if (!new_var || !env)
        return (NULL);
    tmp = env;
    if (tmp->next == NULL)
    {
        new_var->key = key;
        new_var->value = value;
        tmp->next = new_var;
        new_var->next = NULL;
    }
    return (tmp);
}