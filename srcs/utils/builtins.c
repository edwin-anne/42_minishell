/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:54:39 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/06 17:41:15 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "minishell.h"

t_env    *envLast(t_env *env)
{
    t_env   *tmp;
    
    if (!env)
        return (NULL) ;
    tmp = env;
    while (tmp->next != NULL)
        tmp = tmp->next;
    return (tmp);
}   
void    envAddBack(t_env *env, char *key, char *value)
{
    t_env   *tmp;
    t_env   *new;

    new = malloc(sizeof(t_env));
    if (!new || !env)
        return ;
    tmp = envLast(env);
    printf("%s", tmp->key);
    exit(0);
    if (tmp == NULL)
    {
        new->key = key;
        new->value = value;
        tmp->next = new;
        return ;
    }
}
