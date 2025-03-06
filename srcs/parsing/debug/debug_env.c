/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:04:58 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/28 10:06:11 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void print_env_list(t_env *env)
{
    printf("=== Environment Variables ===\n");
    while (env)
    {
        printf("Key: %-20s | Value: %s\n", env->key, env->value);
        env = env->next;
    }
    printf("=============================\n");
}
