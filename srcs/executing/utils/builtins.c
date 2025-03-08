/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:54:39 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/08 14:57:45 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "minishell.h"

/**
 * @brief Useful & necessary functions to make specific builtins working.
 */

t_env   *add_var_back(t_env *env, char *key, char *value)
{
    t_env   *tmp;
    t_env   *new_var;
    
    new_var = malloc(sizeof(t_env));
    if (!new_var || !env)
        return (NULL);
    tmp = env;
    if (tmp->next == NULL)
    {
        new_var->key = key;
        new_var->value = value;
        tmp->next = new_var;
        new_var->next = NULL;
    }
    return (tmp);
}

