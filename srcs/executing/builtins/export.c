/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:29:03 by loribeir          #+#    #+#             */
/*   Updated: 2025/04/27 12:22:36 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

static void	free_env_val(char **env_val)
{
	int	i;

	i = 0;
	while (env_val[i])
	{
		free(env_val[i]);
		i++;
	}
	free(env_val);
}

int	ft_export(t_shell *shell, t_cmd *cmds)
{
	char	**env_val;
	char	*value;
	t_env	*tmp;
	size_t	len;
	int		i;

	tmp = shell->env;
	i = 1;
	shell->exit_status = 0;
	while (cmds->args[i])
	{
		if (verify_args_export(cmds->args[i]) != SUCCESS)
		{
			shell->exit_status = 1;
			i++;
			continue;
		}
		if (ft_strchr(cmds->args[i], '='))
		{
			env_val = ft_split(cmds->args[i], '=');
			if (!env_val || !env_val[0])
			{
				if (env_val)
					free_env_val(env_val);
				shell->exit_status = 1;
				i++;
				continue;
			}
			len = ft_strlen(env_val[0]) + 1;
			value = ft_strdup(cmds->args[i] + len);
			update_export(tmp, ft_strdup(env_val[0]), value);
			free_env_val(env_val);
		}
		else
			update_export(tmp, ft_strdup(cmds->args[i]), NULL);
		i++;
	}
	return (shell->exit_status);
}

int verify_args_export(char *args)
{
	size_t i;
	int has_equal;
	
	i = 0;
	has_equal = 0;
	if (!args || args[0] == '\0')
		return (ft_fdprintf(2, "minishell: export: `': not a valid identifier\n"), FAIL);
	if (args[0] == '=')
		return (ft_fdprintf(2, "minishell: export: `%s': not a valid identifier\n", args), FAIL);
	if (!ft_isalpha(args[0]) && args[0] != '_')
		return (ft_fdprintf(2, "minishell: export: `%s': not a valid identifier\n", args), FAIL);
	
	while (args[i])
	{
		if (args[i] == '=')
		{
			has_equal = 1;
			break;
		}
		if (!ft_isalnum(args[i]) && args[i] != '_')
			return (ft_fdprintf(2, "minishell: export: `%s': not a valid identifier\n", args), FAIL);
		i++;
	}
	
	if (!has_equal && args[i - 1] == '-')
		return (ft_fdprintf(2, "minishell: export: `%s': not a valid identifier\n", args), FAIL);
	
	return (SUCCESS);
}

void    update_export(t_env *tmp, char *key, char *value)
{
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            free(key);
            if (tmp->value)
                free(tmp->value);
            tmp->value = value;
            return;
        }
        if (!tmp->next)
            break;
        tmp = tmp->next;
    }
    add_var_back(tmp, key, value);
}

t_env   *add_var_back(t_env *env, char *key, char *value)
{
    t_env   *tmp;
    t_env   *new_var;
    
    if (!env)
        return (NULL);
    new_var = malloc(sizeof(t_env));
    if (!new_var)
        return (NULL);
    new_var->key = key;
    new_var->value = value;
    new_var->next = NULL;
    
    tmp = env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_var;
    return (env);
}