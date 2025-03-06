/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:14:46 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/05 00:03:38 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *get_env_value(t_env *env, const char *key)
{
    while (env)
    {
        if (strcmp(env->key, key) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

void execute_env_var(t_env *env, char **args)
{
    int i;

	if (!args)
		return ;

	i = 0;
    while (args[i])
    {
        if (args[i][0] == '$')
        {
            char *key = args[i] + 1;
            char *value = get_env_value(env, key);
            
            if (value)
            {
                free(args[i]);
                args[i] = strdup(value);
            }
            else
            {
                free(args[i]);
                args[i] = strdup("");
            }
        }
        i++;
    }
}