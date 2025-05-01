/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:47:49 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/30 10:38:18 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		if (redir->file)
			free(redir->file);
		if (redir->limiter)
			free(redir->limiter);
		redir = redir->next;
		free(tmp);
	}
}

void	free_cmds_next(t_cmd *cmd)
{
	if (cmd->path && cmd->path != cmd->args[0])
		free(cmd->path);
	cmd->path = NULL;
	free_args(cmd);
	if (cmd->redir_in)
	{
		free_redir_list(cmd->redir_in);
		cmd->redir_in = NULL;
	}
	if (cmd->redir_out)
	{
		free_redir_list(cmd->redir_out);
		cmd->redir_out = NULL;
	}
	if (cmd->pipe)
	{
		free(cmd->pipe);
		cmd->pipe = NULL;
	}
}

void	free_args(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			if (cmd->args[i])
				free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
}
