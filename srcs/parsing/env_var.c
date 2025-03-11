/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:14:46 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/09 16:19:38 by Edwin ANNE       ###   ########.fr       */
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

static char *process_env_var(t_env *env, char *str)
{
	char    *result;
	char    *value;
	char    *temp;
	char    *new_result;
	int     i;
	int     j;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !ft_strchr("'\" ", str[i + 1]))
		{
			i++;
			temp = malloc(strlen(str) + 1);
			j = 0;
			while (str[i] && !strchr("'\" $", str[i]))
				temp[j++] = str[i++];
			temp[j] = '\0';
			value = get_env_value(env, temp);
			new_result = ft_strjoin(result, value ? value : "");
			free(result);
			result = new_result;
			free(temp);
			i--;
		}
		else
		{
			if (str[i] != '$')
				name_env_var(str[i], &result);
		}
		i++;
	}
	return (result);
}

void execute_env_var(t_env *env, char **args)
{
	int i;
	char *processed;

	if (!args)
		return;

	i = 0;
	while (args[i])
	{
		processed = process_env_var(env, args[i]);
		free(args[i]);
		args[i] = processed;
		i++;
	}
}

void name_env_var(char c, char **result)
{
	char *temp;
	char *new_result;

	temp = malloc(2);
	if (!temp)
		return;
	temp[0] = c;
	temp[1] = '\0';
	new_result = ft_strjoin(*result, temp);
	free(temp);
	free(*result);
	*result = new_result;
}