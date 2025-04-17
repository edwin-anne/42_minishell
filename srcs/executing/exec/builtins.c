/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:14:13 by lolq              #+#    #+#             */
/*   Updated: 2025/04/17 11:26:03 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief : builtins exec will check which builtins is called and execute the
 * correct ones.
 * if the cmd is inside a pipe or redir, then the cmd should not execute inside
 * the parent.
 */

int builtins_child(t_shell *shell, t_cmd *cmds)
{
    char    **args;

    args = cmds->args;
    if (ft_strcmp(args[0], "echo") == 0)
        return (ft_echo(cmds), SUCCESS);
    if (ft_strcmp(args[0], "pwd") == 0)
        return (ft_pwd(), SUCCESS);
    if (ft_strcmp(args[0], "env") == 0)
        return (ft_env(shell, cmds), SUCCESS);
    if (ft_strcmp(args[0], "export") == 0)
        return(ft_export(shell, cmds), SUCCESS);
    if (ft_strcmp(args[0], "unset") == 0)
        return (ft_unset(shell, cmds->args), SUCCESS); 
    if (ft_strcmp(args[0], "exit") == 0)
        return(ft_exit(shell, cmds), SUCCESS);
    return (FAIL);
}

int builtins_parent(t_shell *shell, t_cmd *cmds)
{
    char    **args;

    args = cmds->args;
    if (cmds->pipe != NULL || cmds->pipe_prev != NULL) 
        return (FAIL);
    if (ft_strcmp(args[0], "export") == 0)
        return(ft_export(shell, cmds), SUCCESS);
    if (ft_strcmp(args[0], "unset") == 0)
        return (ft_unset(shell, cmds->args), SUCCESS); 
    if (ft_strcmp(args[0], "exit") == 0)
        return(ft_exit(shell, cmds), SUCCESS);
    return (FAIL);
}