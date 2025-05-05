/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:38:24 by lolq              #+#    #+#             */
/*   Updated: 2025/05/05 16:32:42 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	create_child(t_shell *shell, t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (!tmp->args || !tmp->args[0] || tmp->args[0][0] == '\0')
		{
			tmp = tmp->next;
			continue ;
		}
		open_pipes(shell, tmp);
		handle_fork(shell, tmp);
		close_pipes(tmp);
		tmp = tmp->next;
	}
	return (FAIL);
}

void	exec_child(t_cmd *cmds, t_shell *shell)
{
	char	**env;
	int		exit_status;

	if (!cmds->args || !cmds->args[0] || cmds->args[0][0] == '\0')
	{
		free_shell(shell);
		exit(0);
	}
	exit_status = 0;
	env = env_char(shell);
	find_executable(cmds, shell->env);
	if (cmds->is_builtin == true)
	{
		handle_builtins_child(shell, cmds, env, exit_status);
		return ;
	}
	handle_ext_cmds(shell, cmds, env);
	free_shell(shell);
	free_char_array(env);
}

void	wait_children(t_shell *shell)
{
	int		last_status;
	int		status;
	t_cmd	*tmp;

	status = 0;
	last_status = 0;
	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->has_child && tmp->pid > 0)
		{
			waitpid(tmp->pid, &status, 0);
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			if (tmp->next == NULL)
				shell->exit_status = last_status;
		}
		tmp = tmp->next;
	}
}
