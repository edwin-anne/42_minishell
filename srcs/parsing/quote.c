/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:12:01 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/24 09:57:20 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int quote(char **args)
{
	int		i;
	int		single_quote_open;
	int		double_quote_open;
	char	*arg;

	i = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		arg = args[i];
		if (!arg[0] || (arg[0] && arg[1] == '"') || (arg[0] && arg[1] == '\''))
			return (0);
		while (*arg)
		{
			if (*arg == '\'' && double_quote_open == 0)
				single_quote_open = !single_quote_open;
			else if (*arg == '"' && single_quote_open == 0)
				double_quote_open = !double_quote_open;
			arg++;
		}
		i++;
	}
	if (single_quote_open || double_quote_open)
		return (0);
	return (1);
}

char	*remove_quotes(const char *arg)
{
	int		i;
	int		j;
	char	quote;
	char	*result;

	if (!arg)
		return (NULL);
	result = malloc(ft_strlen(arg) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '"') && (quote == 0 || quote == arg[i]))
		{
			if (quote == 0)
				quote = arg[i];
			else
				quote = 0;
		}
		else
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