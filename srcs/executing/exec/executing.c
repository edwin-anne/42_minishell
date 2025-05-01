/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:18 by lolq              #+#    #+#             */
/*   Updated: 2025/05/01 12:08:08 by Edwin ANNE       ###   ########.fr       */
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
	t_cmd *current;

	if (!shell || !shell->cmds)
		return (FAIL);
	current = shell->cmds;
	while (current && (!current->args || !current->args[0]) && 
		!current->redir_in && !current->redir_out)
	{
		current = current->next;
	}
	if (!current)
		return (SUCCESS);
	create_child(shell, current);
	wait_children(shell);
	return (SUCCESS);
}
