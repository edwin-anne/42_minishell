/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:08:04 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 12:00:38 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->is_builtin = false;
	cmd->has_child = 0;
	cmd->next = NULL;
	cmd->pipe = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	return (cmd);
}

t_pipe	*init_pipe(void)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->pipe[0] = -1;
	pipe->pipe[1] = -1;
	return (pipe);
}
