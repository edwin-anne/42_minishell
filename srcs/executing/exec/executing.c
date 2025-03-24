/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:18 by lolq              #+#    #+#             */
/*   Updated: 2025/03/24 11:31:59 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief: calling all main functions to make the execution working: 
 *  - builtins exec will check which builtins is called. 
 */

int executing(t_shell *shell)
{
    t_cmd   *tmp;
 
    tmp = shell->cmds;
    while (tmp)
    {
        create_child(shell, shell->cmds);
        wait_children(shell);
        tmp = tmp->next;
    }
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