/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:48:18 by lolq              #+#    #+#             */
/*   Updated: 2025/04/27 11:48:43 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int     handle_redirout(t_shell *shell, t_cmd *cmd)
{
    int fd_out;

    fd_out = 0;
    if (!cmd->redir_out)
        return (0);
    fd_out = check_redir_out(cmd->redir_out);
    if (fd_out < 0)
    {
        if (cmd->next == NULL)
            shell->exit_status = 1;
        return (-1);
    }
    if (fd_out > 0)
        close(fd_out);
    return (SUCCESS);
}

int     handle_redirin(t_shell *shell, t_cmd *cmd)
{
    int fd_in;

    if (!cmd->redir_in)
        return (0); // pas de redir
    fd_in = check_redir_in(cmd->redir_in);
    if (fd_in < 0)
    {
        if (cmd->next == NULL)
            shell->exit_status = 1;
        return (-1); // erreur de redir
    }
    
    if (fd_in > 0)
        close(fd_in);
    return (SUCCESS); // succes
}

void    handle_fork(t_shell *shell, t_cmd *cmd)
{
    pid_t   pid;
    
    if (builtins_parent(shell, cmd) == SUCCESS)
        return ;
    if (handle_redirin(shell, cmd) < 0 || handle_redirout(shell, cmd) < 0)
        return ;
    pid = fork();
    if (pid < 0)
        exit(1); // TODO: ne pas oublier de free la struct (edwin)
    if (pid == 0)
    {
        ft_dup(cmd);
        ft_dup_redir(cmd->redir_in, cmd->redir_out);
        exec_child(cmd, shell);
        exit(0);
    }
    cmd->pid = pid; 
    cmd->has_child = 1; // un enfant a bien été crée
}
