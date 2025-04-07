/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:11:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/07 21:04:33 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	create_pipe(t_cmd *cmds)
{
	t_cmd	*current;
	int		i;
	
	if (!cmds)
		return;
		
	current = cmds;
	while (current)
	{
		current->pipe_in = NULL;
		current->pipe_out = NULL;
		current = current->next;
	}
	current = cmds;
	i = 0;
	while (current && current->next)
	{
		t_pipe *new_pipe = init_redir();
		if (!new_pipe)
		{
			if (new_pipe)
				free(new_pipe);
			return;
		}
		current->pipe_out = new_pipe;
		current->next->pipe_in = new_pipe;
		current = current->next;
		i++;
	}
}