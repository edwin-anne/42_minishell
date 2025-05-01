/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:35:57 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/05/01 11:24:05 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	is_var_char(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	append_str(char **result, const char *str)
{
	char	*new_result;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (*result)
		len1 = ft_strlen(*result);
	if (str)
		len2 = ft_strlen(str);
	new_result = malloc(len1 + len2 + 1);
	if (!new_result)
		return ;
	if (*result)
		ft_strlcpy(new_result, *result, len1 + 1);
	else
		new_result[0] = '\0';
	if (str)
		ft_strlcat(new_result, str, len1 + len2 + 1);
	free(*result);
	*result = new_result;
}

void	handle_dollar_sign(t_shell *shell, char **result, char *str, int *i)
{
	if (!str[*i + 1] || (!is_var_char(str[*i + 1])
			&& str[*i + 1] != '?' && str[*i + 1] != '$'))
		handle_regular_char(result, str[(*i)++]);
	else
	{
		(*i)++;
		if (handle_special_vars(shell, result, str, i))
			return ;
		handle_env_var(shell->env, result, str, i);
	}
}
