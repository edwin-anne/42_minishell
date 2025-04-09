/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:31:28 by lolq              #+#    #+#             */
/*   Updated: 2025/04/09 14:34:51 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int    get_fdin(t_cmd *cmd)
{
    if (cmd->redir_in != NULL)
        return (cmd->redir_in->fd);
    else if (cmd->pipe_in != NULL)
        return (cmd->pipe_in->pipe[0]);
    else 
        return (STDIN_FILENO);
}

int get_fdout(t_cmd *cmd)
{
    if (cmd->redir_out != NULL)
        return (cmd->redir_out->fd);
    else if (cmd->pipe_out != NULL)
        return (cmd->pipe_out->pipe[1]);
    else 
        return (STDOUT_FILENO);
}

void    ft_dup(t_cmd *cmd)
{
    printf("%d\n", ((get_fdin(cmd))));
    printf("%d\n",((get_fdout(cmd))));
    dup2(get_fdin(cmd), STDIN_FILENO);
    dup2(get_fdout(cmd), STDOUT_FILENO);
}