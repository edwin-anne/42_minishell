/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:31:28 by lolq              #+#    #+#             */
/*   Updated: 2025/04/08 18:00:29 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int    get_fdin(t_cmd *cmd)
{
    if (cmd->pipe_in != NULL)
        return (cmd->pipe_in->pipe[1]);
    else if (cmd->redir_in != NULL)
        return (cmd->redir_in->fd);
    else 
        return (1);
}

int get_fdout(t_cmd *cmd)
{
    if (cmd->pipe_out != NULL)
    return (cmd->pipe_out->pipe[0]);
else if (cmd->redir_out != NULL)
    return (cmd->redir_out->fd);
else 
    return (1);
}

void    ft_dup(t_cmd *cmd)
{
    printf("%d\n", ((get_fdin(cmd))));
    printf("%d\n",((get_fdout(cmd))));
    dup2(get_fdin(cmd), STDIN_FILENO);
    dup2(get_fdout(cmd), STDOUT_FILENO);
}