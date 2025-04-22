/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:14:46 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/17 09:34:45 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_special_vars(t_shell *shell, char **res, char *str, int *i)
{
	char	*tmp;

	if (str[*i] == '?')
	{
		tmp = ft_getexitcode(shell);
		append_str(res, tmp);
		free(tmp);
		(*i)++;
		return (1);
	}
	if (str[*i] == '$')
	{
		tmp = ft_getpid();
		append_str(res, tmp);
		free(tmp);
		(*i)++;
		return (1);
	}
	return (0);
}

static void	handle_env_var(t_env *env, char **res, char *str, int *i)
{
	char	var_name[256];
	char	*value;
	int		j;

	j = 0;
	while (str[*i] && is_var_char(str[*i]) && j < 255)
		var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
	value = get_env_value(env, var_name);
	if (value)
		append_str(res, value);
}

static void	handle_regular_char(char **res, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	append_str(res, temp);
}

char	*process_env_var(t_shell *shell, char *str)
{
	char	*result;
	int		i;
	int		in_sq;
	int		in_dq;

	result = strdup("");
	i = 0;
	in_sq = 0;
	in_dq = 0;
	while (str[i])
	{
		if (update_quote_state(str[i], &in_sq, &in_dq))
			i++;
		else if (str[i] == '$' && !in_sq && str[i + 1])
		{
			i++;
			if (handle_special_vars(shell, &result, str, &i))
				continue ;
			handle_env_var(shell->env, &result, str, &i);
		}
		else
			handle_regular_char(&result, str[i++]);
	}
	return (result);
}

void	execute_env_var(t_shell *shell, char **args)
{
	int		i;
	char	*processed;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		processed = process_env_var(shell, args[i]);
		free(args[i]);
		args[i] = processed;
		i++;
	}
}
