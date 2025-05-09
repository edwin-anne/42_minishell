/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:49:26 by lolq              #+#    #+#             */
/*   Updated: 2025/05/06 14:24:16 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	*search_env_path(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PATH" ) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	find_executable(t_cmd *cmds, t_env *env)
{
	char	**path_split;
	char	*path_value;

	if (!cmds->args || !cmds->args[0] || cmds->args[0][0] == '\0')
		return ;
	if (cmds->is_builtin == true)
		return ;
	if (ft_strchr(cmds->args[0], '/'))
	{
		cmds->path = cmds->args[0];
		return ;
	}
	path_value = search_env_path(env);
	if (!path_value)
		return ;
	path_split = ft_split(path_value, ':');
	if (!path_split)
		return ;
	cmds->path = search_in_path(cmds->args[0], path_split);
	free_char_array(path_split);
}

char	*search_in_path(char *cmd, char **path_split)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	exec_error(t_shell *shell, t_cmd *cmds)
{
	if (!cmds->args[0] || cmds->args[0][0] == '\0')
	{
		ft_fdprintf(2, "minishell: %s: command not found\n", cmds->args[0]);
		shell->exit_status = 127;
		return (127);
	}
	if (!cmds->path || access(cmds->path, F_OK) == -1)
	{
		if (ft_strchr(cmds->args[0], '/'))
			ft_fdprintf(2, MSG_FILEDIRECTORY, cmds->args[0]);
		else
			ft_fdprintf(2, "minishell: %s: command not found\n", cmds->args[0]);
		shell->exit_status = 127;
		return (127);
	}
	return (exec_error_perm(shell, cmds));
}

int	exec_error_perm(t_shell *shell, t_cmd *cmds)
{
	struct stat	st;

	if (stat(cmds->path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_fdprintf(2, "minishell: %s: Is a directory\n", cmds->args[0]);
		shell->exit_status = 126;
		return (126);
	}
	if (access(cmds->path, X_OK) == -1)
	{
		ft_fdprintf(2, "minishell: %s: Permission denied\n", cmds->args[0]);
		shell->exit_status = 126;
		return (126);
	}
	shell->exit_status = 0;
	return (SUCCESS);
}
