/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:33:27 by lolq              #+#    #+#             */
/*   Updated: 2025/04/27 14:16:17 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void    ft_dup(t_cmd *cmd)
{
    int get_in;
    int get_out;

    get_in = get_fdin(cmd);
    get_out = get_fdout(cmd);
    if (get_in != STDIN_FILENO && get_in >= 0)
    {
        dup2(get_in, STDIN_FILENO);
        close(get_in);
    }
    if (get_out != STDOUT_FILENO && get_out >= 0)
    {
        dup2(get_out, STDOUT_FILENO);
        close(get_out);
    }
    if (cmd->pipe)
    {
        if (cmd->pipe->pipe[0] != get_in && cmd->pipe->pipe[0] >= 0)
            close(cmd->pipe->pipe[0]);
        if (cmd->pipe->pipe[1] != get_out && cmd->pipe->pipe[1] >= 0)
            close(cmd->pipe->pipe[1]);
    }
    if (cmd->pipe_prev && *cmd->pipe_prev != get_in && *cmd->pipe_prev >= 0)
        close(*cmd->pipe_prev);
}

int    get_fdin(t_cmd *cmd)
{
    if (cmd->redir_in != NULL)
        return (cmd->redir_in->fd);
    else if (cmd->pipe_prev != NULL)
        return (*cmd->pipe_prev);
    else 
        return (STDIN_FILENO);
}

int get_fdout(t_cmd *cmd)
{
    if (cmd->redir_out != NULL)
        return (cmd->redir_out->fd);
    else if (cmd->pipe && cmd->pipe->pipe[1] != -1)
        return (cmd->pipe->pipe[1]);
    else 
        return (STDOUT_FILENO);
}
