/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:56:19 by lolq              #+#    #+#             */
/*   Updated: 2025/05/04 11:43:46 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	**env_char(t_shell *shell)
{
	char	**result;
	char	*key_eq;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = shell->env;
	result = malloc(sizeof(char *) * (env_len(tmp) + 1));
	if (!result)
		return (NULL);
	while (tmp)
	{
		key_eq = ft_strjoin(tmp->key, "=");
		if (!key_eq)
			return (free_char_array(result), NULL);
		result[i] = ft_strjoin(key_eq, tmp->value);
		free(key_eq);
		if (!result[i])
			return (free_char_array(result), NULL);
		tmp = tmp->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	env_len(t_env *env)
{
	t_env	*tmp;
	int		res;

	res = 0;
	tmp = env;
	while (tmp)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

void	handle_builtins_child(t_shell *shell, t_cmd *cmd, char **env, \
	int exit_status)
{
	builtins_child(shell, cmd);
	exit_status = shell->exit_status;
	free_shell(shell);
	free_char_array(env);
	exit(exit_status);
}

void	handle_ext_cmds(t_shell *shell, t_cmd *cmd, char **env)
{
	int	error;
	int	exit_status;

	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0'
        || (ft_strchr(cmd->args[0], '=') && !ft_strchr(cmd->args[0], '/')))
    {
        free_shell(shell);
        free_char_array(env);
        exit(0);
    }
	exit_status = 0;
	error = exec_error(shell, cmd);
	if (error)
	{
		exit_status = shell->exit_status;
		free_shell(shell);
		free_char_array(env);
		exit(exit_status);
	}
	if (execve(cmd->path, cmd->args, env) == -1)
	{
		free_shell(shell);
		free_char_array(env);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}
