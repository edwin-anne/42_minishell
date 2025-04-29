/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:11:05 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 13:43:44 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_parenthesis_char(char c, int *in_sq, int *in_dq, int *count)
{
	if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
	else if (c == '"' && !(*in_sq))
		*in_dq = !(*in_dq);
	else if (c == '(' && !(*in_sq) && !(*in_dq))
		(*count)++;
	else if (c == ')' && !(*in_sq) && !(*in_dq))
	{
		(*count)--;
		if (*count < 0)
			return (0);
	}
	return (1);
}

void	process_remove_parenthesis(const char *arg, char *result,
									int *j, int *quotes)
{
	int	i;
	int	*in_sq;
	int	*in_dq;

	in_sq = &quotes[0];
	in_dq = &quotes[1];
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && !(*in_dq))
			*in_sq = !(*in_sq);
		else if (arg[i] == '"' && !(*in_sq))
			*in_dq = !(*in_dq);
		if ((arg[i] != '(' && arg[i] != ')') || *in_sq || *in_dq)
			result[(*j)++] = arg[i];
		i++;
	}
	result[*j] = '\0';
}

int	handle_empty_result(char *result, const char *arg, int j)
{
	if (j == 0 && arg[0] != '\0')
	{
		free(result);
		return (1);
	}
	return (0);
}
