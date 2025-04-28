/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:48:40 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 18:20:31 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	update_quotes_calc(char c, int *in_sq, int *in_dq)
{
	if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
	else if (c == '"' && !(*in_sq))
		*in_dq = !(*in_dq);
}

static int	add_space_size(const char *line, int i)
{
	int	count;

	count = 0;
	if (i > 0 && line[i - 1] != ' ' && line[i] != line[i - 1])
		count++;
	if (line[i + 1] && line[i + 1] != ' ' && line[i] != line[i + 1])
		count++;
	return (count);
}

static int	calculate_buffer_size(const char *line)
{
	int	size;
	int	i;
	int	in_sq;
	int	in_dq;

	size = 0;
	i = 0;
	in_sq = 0;
	in_dq = 0;
	while (line[i])
	{
		update_quotes_calc(line[i], &in_sq, &in_dq);
		if (!in_sq && !in_dq && is_operator(line[i]))
			size += add_space_size(line, i);
		size++;
		i++;
	}
	return (size);
}

char	*pre_parsing(char *line)
{
	char	*new_line;
	int		i;
	int		j;
	int		in_sq;
	int		in_dq;

	if (!line)
		return (NULL);
	new_line = malloc(sizeof(char) * (calculate_buffer_size(line) + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	in_sq = 0;
	in_dq = 0;
	while (line[i])
	{
		update_quotes(line[i], &in_sq, &in_dq);
		if (!in_sq && !in_dq && is_operator(line[i]))
			handle_operator(new_line, line, &i, &j);
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}
