/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:33:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/22 11:56:56 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env	*add_env_node(t_env *node, char *env)
{
	t_env	*new_value;
	char	*sep;

	new_value = malloc(sizeof(t_env));
	if (!new_value)
		return (NULL);
	sep = ft_strchr(env, '=');
	if (sep)
	{
		new_value->key = strndup(env, sep - env);
		new_value->value = strdup(sep + 1);
	}
	else
	{
		new_value->key = strdup(env);
		new_value->value = NULL;
	}
	new_value->next = node;
	return (new_value);
}

t_env	*copy_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		env = add_env_node(env, envp[i]);
		i++;
	}
	return (env);
}
