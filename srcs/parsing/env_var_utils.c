/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:35:57 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 13:37:39 by Edwin ANNE       ###   ########.fr       */
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
	if (isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	append_str(char **result, const char *str)
{
	char	*new_result;

	new_result = malloc(ft_strlen(*result) + ft_strlen(str) + 1);
	if (!new_result)
		return ;
	ft_strlcpy(new_result, *result, ft_strlen(*result) + 1);
	ft_strlcat(new_result, str, ft_strlen(*result) + ft_strlen(str) + 1);
	free(*result);
	*result = new_result;
}

int	update_quote_state(char c, int *in_sq, int *in_dq)
{
	if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
	else if (c == '\"' && !(*in_sq))
		*in_dq = !(*in_dq);
	else
		return (0);
	return (1);
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
