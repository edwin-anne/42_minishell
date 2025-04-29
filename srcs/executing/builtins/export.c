/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:29:03 by loribeir          #+#    #+#             */
/*   Updated: 2025/04/29 17:12:21 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

int	ft_export(t_shell *shell, t_cmd *cmds)
{
	t_env	*env;
	int		i;

	env = shell->env;
	i = 1;
	shell->exit_status = 0;
	while (cmds->args[i])
	{
		handle_arg_export(shell, env, cmds->args[i]);
		i++;
	}
	return (shell->exit_status);
}

int	handle_arg_export(t_shell *shell, t_env *env, char *arg)
{
	char	**env_val;
	char	*value;
	size_t	len;

	if (verify_args_export(arg) != SUCCESS)
		return (shell->exit_status = 1, FAIL);
	if (ft_strchr(arg, '='))
	{
		env_val = ft_split(arg, '=');
		if (!env_val || !env_val[0])
		{
			if (env_val)
				free_env_val(env_val);
			return (shell->exit_status = 1, FAIL);
		}
		len = ft_strlen(env_val[0]) + 1;
		value = ft_strdup(arg + len);
		update_export(env, ft_strdup(env_val[0]), value);
		free_env_val(env_val);
	}
	else
		update_export(env, ft_strdup(arg), NULL);
	return (SUCCESS);
}

int	verify_args_export(char *args)
{
	size_t	i;
	int		has_equal;

	i = 0;
	has_equal = 0;
	if (!args || args[0] == '\0')
		return (ft_fdprintf(2, MSG_NOIDENTIFIER), FAIL);
	if (args[0] == '=')
		return (ft_fdprintf(2, MSG_IDENTIFIER, args), FAIL);
	if (!ft_isalpha(args[0]) && args[0] != '_')
		return (ft_fdprintf(2, MSG_IDENTIFIER, args), FAIL);
	while (args[i])
	{
		if (args[i] == '=')
		{
			has_equal = 1;
			break ;
		}
		if (!ft_isalnum(args[i]) && args[i] != '_')
			return (ft_fdprintf(2, MSG_IDENTIFIER, args), FAIL);
		i++;
	}
	if (!has_equal && args[i - 1] == '-')
		return (ft_fdprintf(2, MSG_IDENTIFIER, args), FAIL);
	return (SUCCESS);
}

void	update_export(t_env *tmp, char *key, char *value)
{
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(key);
			if (tmp->value)
				free(tmp->value);
			tmp->value = value;
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	add_var_back(tmp, key, value);
}

void	free_env_val(char **env_val)
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
