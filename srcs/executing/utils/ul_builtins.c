/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ul_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:54:39 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/09 15:25:31 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "minishell.h"

/**
 * @brief Useful & necessary functions to make specific builtins working.
 */

t_env   *search_lst(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void    free_node_env(t_env *env)
{
	if (env)
	{
    	free(env->key);
    	free(env->value);
    	free(env);
	}
}
