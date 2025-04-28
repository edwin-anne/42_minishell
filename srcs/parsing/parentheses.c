/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:45:19 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 12:03:42 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_parentheses(char **args)
{
	int	i;
	int	j;
	int	count;
	int	in_sq;
	int	in_dq;

	i = 0;
	count = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		j = 0;
		in_sq = 0;
		in_dq = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\'' && !in_dq)
				in_sq = !in_sq;
			else if (args[i][j] == '"' && !in_sq)
				in_dq = !in_dq;
			else if (args[i][j] == '(' && !in_sq && !in_dq)
				count++;
			else if (args[i][j] == ')' && !in_sq && !in_dq)
			{
				count--;
				if (count < 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (count == 0);
}

char	*remove_parentheses(const char *arg)
{
	int		i;
	int		j;
	char	*result;
	int		in_sq;
	int		in_dq;

	if (!arg)
		return (NULL);
	result = malloc(ft_strlen(arg) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_sq = 0;
	in_dq = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (arg[i] == '"' && !in_sq)
			in_dq = !in_dq;
		if ((arg[i] != '(' && arg[i] != ')') || in_sq || in_dq)
			result[j++] = arg[i];
		i++;
	}
	result[j] = '\0';
	if (j == 0 && arg[0] != '\0')
	{
		free(result);
		return (ft_strdup(arg));
	}
	return (result);
}

void	interpret_parentheses(char **args)
{
	int		i;
	char	*processed;

	i = 0;
	if (!args)
		return ;
	if (!check_parentheses(args))
	{
		ft_fdprintf(2, "minishell: syntax error near unexpected token `('\n");
		return ;
	}
	while (args[i])
	{
		processed = remove_parentheses(args[i]);
		if (processed)
		{
			free(args[i]);
			args[i] = processed;
		}
		i++;
	}
}
