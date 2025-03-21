/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:14:46 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/21 13:33:55 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return(env->value);
		env = env->next;
	}
	return(NULL);
}

static int	is_var_char(char c)
{
	if (isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void append_str(char **result, const char *str)
{
	char	*new_result; 
	
	new_result = malloc(strlen(*result) + strlen(str) + 1);
	if (!new_result)
		return ;
	ft_strlcpy(new_result, *result, ft_strlen(*result) + 1);
	ft_strlcat(new_result, str, ft_strlen(*result) + ft_strlen(str) + 1);
	free(*result);
	*result = new_result;
}

static char *process_env_var(t_env *env, char *str)
{
	char *result;
	char *value;
	char var_name[256];
	char temp[2];
	int i;
	int	j;

	result = strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i] == '?')
			{
				append_str(&result, ft_getexitcode());
				i++;
				continue;
			}

			if (str[i] == '$')
			{
				append_str(&result, ft_getpid());
				i++;
				continue;
			}

			j = 0;
			while (str[i] && is_var_char(str[i]) && j < 255)
				var_name[j++] = str[i++];
			var_name[j] = '\0';

			value = get_env_value(env, var_name);
			if (value)
				append_str(&result, value);
			else
			{
				append_str(&result, "$");
				append_str(&result, var_name);
			}
		}
		else
		{
			temp[0] = str[i];
			temp[1] = '\0';
			append_str(&result, temp);
			i++;
		}
	}
	return (result);
}

void execute_env_var(t_env *env, char **args)
{
	int i;
	char *processed;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
	{
		processed = process_env_var(env, args[i]);
		free(args[i]);
		args[i] = processed;
	}
}
