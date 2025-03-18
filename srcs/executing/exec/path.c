/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:49:26 by lolq              #+#    #+#             */
/*   Updated: 2025/03/18 18:01:13 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char    *search_env_path(t_env *env, t_cmd *cmds)
{
    int     i;
    t_env   *tmp;

    tmp = env;
    while (tmp->next != NULL)
    {
        if (ft_strcmp(tmp->key, "PATH" ) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

char    *find_exec(t_cmd *cmds, t_env *env)
{
    char    *tmp;
    char    **path_value;
    
    path_value = ft_split(search_env_path(env, cmds), ":");
    
}