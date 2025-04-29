/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:23:06 by lolq              #+#    #+#             */
/*   Updated: 2025/04/28 13:07:45 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	open_pipes(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->pipe)
		return ;
	if (cmd->next && cmd->pipe->pipe[0] == -1 && cmd->pipe->pipe[1] == -1)
	{
		if (pipe(cmd->pipe->pipe) == -1)
		{
			ft_fdprintf(2, "bash: pipe error: Too many open files\n");
			ft_fdprintf(2, "bash: start_pipeline: pgrp pipe:  \
				Too many open files\n");
			shell->exit_status = 129;
			return ;
		}
		if (cmd->next && cmd->pipe->pipe[0] != -1)
			cmd->next->pipe_prev = &(cmd->pipe->pipe[0]);
	}
}

void	close_pipes(t_cmd *cmd)
{
	if (cmd->pipe && cmd->pipe->pipe[1] != -1)
	{
		close(cmd->pipe->pipe[1]);
		cmd->pipe->pipe[1] = -1;
	}
	if (cmd->next == NULL && cmd->pipe_prev != NULL && *cmd->pipe_prev != -1)
	{
		close(*cmd->pipe_prev);
		*cmd->pipe_prev = -1;
	}
}
