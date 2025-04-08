/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:40:34 by lolq              #+#    #+#             */
/*   Updated: 2025/04/08 17:24:51 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void    open_pipes(t_shell *shell, t_cmd *cmds)
{

    if (cmds->pipe_in != NULL && cmds->pipe_in->pipe[0] == -1 && cmds->pipe_in->pipe[1] == -1)
    {
        if (pipe(cmds->pipe_in->pipe) == -1)
        {
            ft_fdprintf(2, "bash: pipe error: Too many open files\n");
            ft_fdprintf(2, "bash: start_pipeline: pgrp pipe: Too many open files\n");
            shell->exit_status = 129;
        }
    }
    if (cmds->pipe_out != NULL && cmds->pipe_out->pipe[0] == -1 && cmds->pipe_out->pipe[1] == -1)
    {
        if (pipe(cmds->pipe_out->pipe) == -1)
        {
            ft_fdprintf(2, "bash: start_pipeline: pgrp pipe: Too many open files\n");
            ft_fdprintf(2, "bash: pipe error: Too many open files\n");
            shell->exit_status = 129;
        }
    }
}
