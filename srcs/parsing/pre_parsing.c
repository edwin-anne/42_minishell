/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:48:40 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/24 17:18:49 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	calculate_buffer_size(const char *line)
{
	int	size;
	int	i;
	int in_sq;
	int in_dq;

	size = 0;
	i = 0;
	in_sq = 0;
	in_dq = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (line[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else if (!in_sq && !in_dq && (line[i] == '|' || line[i] == '<' || line[i] == '>'))
		{
			if (i > 0 && line[i - 1] != ' '
				&& !(i > 0 && line[i] == line[i - 1]))
				size++;
			if (line[i + 1] && line[i + 1] != ' '
				&& !(line[i + 1] == line[i]))
				size++;
		}
		size++;
		i++;
	}
	return (size);
}

char	*pre_parsing(char *line)
{
	char	*new_line;
	int		j;
	int		i;
	int     in_sq;
	int     in_dq;

	if (!line)
		return (NULL);
	new_line = malloc(sizeof(char) * (calculate_buffer_size(line) + 1));
	if (!new_line)
		return (NULL);
	j = 0;
	i = 0;
	in_sq = 0;
	in_dq = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (line[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else if (!in_sq && !in_dq && (line[i] == '|' || line[i] == '<' || line[i] == '>'))
		{
			if (i > 0 && line[i - 1] != ' ' && (line[i] != line[i - 1]))
				new_line[j++] = ' ';
			new_line[j++] = line[i];
			if (line[i + 1] && line[i + 1] != ' ' && (line[i + 1] != line[i]))
				new_line[j++] = ' ';
			i++;
			continue;
		}
		new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}
