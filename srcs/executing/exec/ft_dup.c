/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:33:27 by lolq              #+#    #+#             */
/*   Updated: 2025/04/15 08:54:30 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void    ft_dup(t_cmd *cmd)
{
    int get_in;
    int get_out;

    get_in = get_fdin(cmd);
    get_out = get_fdout(cmd);
    if (get_in != STDIN_FILENO)
    {
        dup2(get_in, STDIN_FILENO);
        close(get_in);
    }
    if (get_out != STDOUT_FILENO)
    {
        dup2(get_out, STDOUT_FILENO);
        close(get_out);
    }
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
