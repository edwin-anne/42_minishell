/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:45:19 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 13:41:30 by Edwin ANNE       ###   ########.fr       */
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
			if (!process_parenthesis_char(args[i][j], &in_sq, &in_dq, &count))
				return (0);
			j++;
		}
		i++;
	}
	return (count == 0);
}

char	*remove_parentheses(const char *arg)
{
	char	*result;
	int		j;
	int		quotes[2];

	if (!arg)
		return (NULL);
	result = malloc(ft_strlen(arg) + 1);
	if (!result)
		return (NULL);
	j = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	process_remove_parenthesis(arg, result, &j, quotes);
	if (handle_empty_result(result, arg, j))
		return (ft_strdup(arg));
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
