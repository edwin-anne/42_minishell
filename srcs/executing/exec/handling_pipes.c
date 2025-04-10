/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:23:06 by lolq              #+#    #+#             */
/*   Updated: 2025/04/10 11:48:28 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void    open_pipes(t_shell *shell, t_cmd *cmd)
{
    if (cmd->pipe != NULL)
    {
        if (cmd->pipe->pipe[0] == -1 && cmd->pipe->pipe[1] == -1)
        {
            if (pipe(cmd->pipe->pipe) == -1)
            {
                ft_fdprintf(2, "bash: pipe error: Too many open files\n");
                ft_fdprintf(2, "bash: start_pipeline: pgrp pipe: Too many open files\n");
                shell->exit_status = 129;
            }
        } 
    }
}
