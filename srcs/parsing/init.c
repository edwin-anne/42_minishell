/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:08:04 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/09 16:19:57 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *init_cmd(void)
{
	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->is_builtin = false;
	cmd->next = NULL;
	
	cmd->redir = (t_redir *)malloc(sizeof(t_redir));
	if (!cmd->redir)
	{
		free(cmd);
		return (NULL);
	}
	
	cmd->redir->type_in = NONE;
	cmd->redir->file_in = NULL;
	cmd->redir->fd_in = -1;
	cmd->redir->limiter_here_doc = NULL;
	cmd->redir->type_out = NONE;
	cmd->redir->file_out = NULL;
	cmd->redir->fd_out = -1;
	
	return (cmd);
}
