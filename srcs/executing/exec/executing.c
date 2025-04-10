/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:18 by lolq              #+#    #+#             */
/*   Updated: 2025/04/08 13:50:01 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"
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
    print_cmd_list(shell->cmds);
    create_child(shell, shell->cmds);
    wait_children(shell);
    return (SUCCESS);
}