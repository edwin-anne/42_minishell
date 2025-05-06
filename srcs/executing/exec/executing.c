/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:22:18 by lolq              #+#    #+#             */
/*   Updated: 2025/05/06 15:15:18 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

t_cmd *skip_empty_commands(t_cmd *current, t_shell *shell)
{
	while (current)
	{
		if ((!current->args || !current->args[0] || current->args[0][0] == '\0') &&
			(current->redir_in || current->redir_out))
		{
			handle_redirin(shell, current);
			handle_redirout(shell, current);
			current = current->next;
			continue;
		}
		if (!current->args || !current->args[0] || current->args[0][0] == '\0')
		{
			current = current->next;
			continue;
		}
		break;
	}
	return (current);
}

int executing(t_shell *shell)
{
	t_cmd *current;

	if (!shell || !shell->cmds)
		return (FAIL);
	current = shell->cmds;
	current = skip_empty_commands(current, shell);
	if (!current)
		return (SUCCESS);
	create_child(shell, current);
	wait_children(shell);
	return (SUCCESS);
}

