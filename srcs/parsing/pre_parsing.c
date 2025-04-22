/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:48:40 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/22 10:54:15 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	calculate_buffer_size(const char *line)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
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

	if (!line)
		return (NULL);
	new_line = malloc(sizeof(char) * (calculate_buffer_size(line) + 1));
	if (!new_line)
		return (NULL);
	j = 0;
	i = 0;
	while (line[i])
	{
		if (i > 0 && (line[i] == '|' || line[i] == '<' || line[i] == '>')
			&& line[i - 1] != ' ' && (line[i] != line[i - 1]))
			new_line[j++] = ' ';
		new_line[j++] = line[i];
		if ((line[i] == '|' || line[i] == '<' || line[i] == '>')
			&& line[i + 1] && line[i + 1] != ' ' && (line[i + 1] != line[i]))
			new_line[j++] = ' ';
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
