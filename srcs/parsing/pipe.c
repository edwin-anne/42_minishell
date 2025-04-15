/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:11:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/10 11:59:42 by lolq             ###   ########.fr       */
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
        current->pipe_prev = NULL;  // Initialiser à NULL au lieu de -1
        current = current->next;
    }
    current = cmds;
    while (current && current->next)
    {
        current->pipe = init_pipe();
        if (!current->pipe)
            return ;
        if (current->next)
            current->next->pipe_prev = &(current->pipe->pipe[1]);  // Assigner l'adresse
        current = current->next;
    }
}