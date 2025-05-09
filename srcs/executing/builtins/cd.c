/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:41:45 by lolq              #+#    #+#             */
/*   Updated: 2025/05/01 11:04:30 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	ft_cd(t_shell *shell, t_cmd *cmds, t_env *env)
{
	char	*path;
	char	current_dir[PATH_MAX];
	int		arg_count;

	path = ft_cd_path(env, cmds);
	if (!path)
		return (cd_error(shell, "HOME not set", NULL));
	arg_count = 0;
	while (cmds->args && cmds->args[arg_count])
		arg_count++;
	if (arg_count > 2)
		return (cd_error(shell, "too many arguments", "cd"));
	if (chdir(path) != 0)
		return (cd_error(shell, strerror(errno), path));
	if (!getcwd(current_dir, sizeof(current_dir)))
		return (cd_error(shell, strerror(errno),
				"error getting current directory"));
	update_env(env, "PWD", current_dir);
	shell->exit_status = 0;
	return (SUCCESS);
}

char	*ft_cd_path(t_env *env, t_cmd *cmds)
{
	char	*home;

	if (!cmds->args[1])
	{
		home = get_env(env, "HOME");
		if (!home)
			return (NULL);
		return (home);
	}
	return (cmds->args[1]);
}

int	cd_error(t_shell *shell, char *msg, char *arg)
{
	shell->exit_status = 1;
	if (arg)
		ft_fdprintf(2, "minishell: %s: %s\n", arg, msg);
	else
		ft_fdprintf(2, "minishell: %s\n", msg);
	return (FAIL);
}

void	update_env(t_env *tmp, char *str, char *current_dir)
{
	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(current_dir);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*get_env(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_constcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
