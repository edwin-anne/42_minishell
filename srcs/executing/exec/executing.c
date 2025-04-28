/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:18 by lolq              #+#    #+#             */
/*   Updated: 2025/04/28 17:30:21 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
/**
 * @brief: main execution orchestrator for the minishell
 * - open_ds() : handles input/output redir.  
 * - create_child() : process creation and cmd execution.
 * - wait_children() : ensures process cleanup. 
 */

int	executing(t_shell *shell)
{
	if (!shell || !shell->cmds || !shell->cmds->args)
		return (FAIL);
	if (shell->cmds->args[0][0] == '\0' && shell->cmds->args[1] == NULL)
		return (FAIL);
	create_child(shell, shell->cmds);
	wait_children(shell);
	return (SUCCESS);
}
