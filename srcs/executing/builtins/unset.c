/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:41:43 by loribeir          #+#    #+#             */
/*   Updated: 2025/05/04 10:20:10 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executing.h"

void	ft_unset(t_shell *shell, char **args)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 0;
	while (args[i])
	{
		tmp = shell->env;
		prev = NULL;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, args[i]) == 0)
			{
				if (prev == NULL)
					shell->env = tmp->next;
				else
					prev->next = tmp->next;
				free_node_env(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}
