/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:18 by lolq              #+#    #+#             */
/*   Updated: 2025/05/04 10:19:11 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

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
