/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:18 by lolq              #+#    #+#             */
/*   Updated: 2025/04/07 18:15:44 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief: main execution orchestrator for the minishell
 * - open_ds() : handles input/output redir.  
 * - create_child() : process creation and cmd execution.
 * - wait_children() : ensures process cleanup. 
 */

int executing(t_shell *shell)
{
    if (!shell || !shell->cmds)
        return (FAIL);
    open_fds(shell->cmds);
    create_child(shell, shell->cmds);
    wait_children(shell);
    return (SUCCESS);
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