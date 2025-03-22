/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:18 by lolq              #+#    #+#             */
/*   Updated: 2025/03/22 17:24:28 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief: calling all main functions to make the execution working: 
 *  - builtins exec will check which builtins is called. 
 *  - 
 */

int    builtins_executing(t_shell *shell, t_cmd *cmds)
{
    char    **args;

    args = cmds->args;
    if (ft_strcmp(args[0], "echo") == 0)
        return (ft_echo(cmds), SUCCESS);
    if (ft_strcmp(args[0], "cd") == 0)
        return (ft_cd(cmds, shell->env), SUCCESS);
    if (ft_strcmp(args[0], "pwd") == 0)
        return (ft_pwd(), SUCCESS);
    if (ft_strcmp(args[0], "env") == 0)
        return (ft_env(shell, cmds), SUCCESS);
    if (ft_strcmp(args[0], "exit") == 0)
        return(ft_exit(shell, cmds), SUCCESS);
    if (ft_strcmp(args[0], "export") == 0)
        return(ft_export(shell, cmds->args), SUCCESS);
    if (ft_strcmp(args[0], "unset") == 0)
        return (ft_unset(shell, cmds->args), SUCCESS);
    return (FAIL);
}

/**
 * int  ft_executing(t_shell *shell)
 *{
 *  while (shell->cmds)
 *  {
 *  create_child     
 *  builtins_exec
 *  search_path
 *  open_pipe
 *  open_fd
 *  }
 *}
 */