/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:12:01 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 16:35:56 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	quote(char **args)
{
	int		i;
	int		j;
	int		single_quote_open;
	int		double_quote_open;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		j = 0;
		single_quote_open = 0;
		double_quote_open = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\'' && !double_quote_open)
				single_quote_open = !single_quote_open;
			else if (args[i][j] == '"' && !single_quote_open)
				double_quote_open = !double_quote_open;
			j++;
		}
		i++;
	}
	return (1);
}

char	*remove_quotes(const char *arg)
{
	int		i;
	int		j;
	int		start_quote;
	char	*result;

	result = malloc(ft_strlen(arg) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	start_quote = 0;
	while (arg[i])
	{
		if ((arg[i] == '"' || arg[i] == '\'') && !start_quote)
			start_quote = arg[i];
		else if (arg[i] == start_quote)
			start_quote = 0;
		else
			result[j++] = arg[i];
		i++;
	}
	result[j] = '\0';
	if (start_quote || !*result)
		return (free(result), ft_strdup(arg));
	return (result);
}

void	interpret_quotes(char **args)
{
	int		i;
	char	*processed;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		processed = remove_quotes(args[i]);
		if (processed)
		{
			free(args[i]);
			args[i] = processed;
		}
		i++;
	}
}
