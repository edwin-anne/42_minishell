/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:48:18 by lolq              #+#    #+#             */
/*   Updated: 2025/04/30 13:56:25 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	handle_fork(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	if (builtins_parent(shell, cmd) == SUCCESS)
		return ;
	if (handle_redirin(shell, cmd) < 0)
		return ;
	if (handle_redirout(shell, cmd) < 0)
		return ;
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		ft_dup(cmd);
		ft_dup_redir(cmd->redir_in, cmd->redir_out);
		exec_child(cmd, shell);
		exit(0);
	}
	close_pipes(cmd);
	close_unused_pipes(shell->cmds, cmd);
	cmd->pid = pid;
	cmd->has_child = 1;
}

int	handle_redirout(t_shell *shell, t_cmd *cmd)
{
	int	fd_out;

	fd_out = 0;
	if (!cmd->redir_out)
		return (0);
	fd_out = check_redir_out(cmd->redir_out);
	if (fd_out < 0)
	{
		if (cmd->next == NULL)
			shell->exit_status = 1;
		return (-1);
	}
	if (fd_out > 0)
		close(fd_out);
	return (SUCCESS);
}

int	handle_redirin(t_shell *shell, t_cmd *cmd)
{
	int	fd_in;

	if (!cmd->redir_in)
		return (0);
	fd_in = check_redir_in(cmd->redir_in);
	if (fd_in < 0)
	{
		if (cmd->next == NULL)
			shell->exit_status = 1;
		return (-1);
	}
	if (fd_in > 0)
		close(fd_in);
	return (SUCCESS);
}

void	close_unused_pipes(t_cmd *cmds, t_cmd *current)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp != current && tmp->pipe)
		{
			if (tmp->pipe->pipe[0] != -1)
			{
				close(tmp->pipe->pipe[0]);
				tmp->pipe->pipe[0] = -1;
			}
			if (tmp->pipe->pipe[1] != -1)
			{
				close(tmp->pipe->pipe[1]);
				tmp->pipe->pipe[1] = -1;
			}
		}
		tmp = tmp->next;
	}
}
