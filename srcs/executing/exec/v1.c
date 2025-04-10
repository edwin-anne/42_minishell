/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes,fds&dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:02:29 by lolq              #+#    #+#             */
/*   Updated: 2025/04/10 11:29:27 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/*void    handling_open(t_redir *redir, int flags, mode_t mode)
{
    if (!redir || !redir->file)
        return ;
    redir->fd = open(redir->file, flags, mode);
	if (redir->fd < 0)
	{
		perror(redir->file);
		redir->fd = -1;
	}
}

void   open_fds(t_cmd *cmds)
{
    t_redir *mult_in;
    t_redir *mult_out;

    mult_in = cmds->redir_in;
    mult_out = cmds->redir_out;
    while (mult_in)
    {
        if (mult_in && mult_in->type == INPUT_REDIR)
            handling_open(mult_in, O_RDONLY, 0);
        if (mult_in && mult_in->type == HEREDOC)
            handling_open(mult_in, O_RDONLY, 0);
        mult_in = mult_in->next;
    }
    while (mult_out)
    {
        if (mult_out && mult_out->type == OUTPUT_REDIR)
            handling_open(mult_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (mult_out && mult_out->type == APPEND_REDIR)
            handling_open(mult_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
        mult_out = mult_out->next;
    }
    cmds = cmds->next;
}

void   close_fds(t_cmd  *cmds)
{
    t_redir *mult_in;
    t_redir *mult_out;

    mult_in = cmds->redir_in;
    mult_out = cmds->redir_out;
    while (mult_in)
    {
        if (mult_in->fd != -1)
            ft_close_fds(mult_in);                
        mult_in = mult_in->next;
    }
    while (mult_out)
    {
        if (mult_out->fd != -1)
            ft_close_fds(mult_out);
        mult_out = mult_out->next;
    }
    cmds = cmds->next;
}

void    ft_close_fds(t_redir *fd)
{
    close(fd->fd);
    fd->fd = -1;    
}

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
}*/