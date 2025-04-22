/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:11:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/17 09:54:15 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	create_pipe(t_cmd *cmds)
{
	t_cmd	*current;

	if (!cmds)
		return ;
	current = cmds;
	while (current)
	{
		current->pipe = NULL;
		current->pipe_prev = NULL;
		current = current->next;
	}
	current = cmds;
	while (current && current->next)
	{
		current->pipe = init_pipe();
		if (!current->pipe)
			return ;
		if (current->next)
			current->next->pipe_prev = &(current->pipe->pipe[1]);
		current = current->next;
	}
}
