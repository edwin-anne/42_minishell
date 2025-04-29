/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:16:51 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 18:17:19 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	update_quotes(char c, int *in_sq, int *in_dq)
{
	if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
	else if (c == '"' && !(*in_sq))
		*in_dq = !(*in_dq);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	handle_operator(char *new_line, char *line, int *i, int *j)
{
	if (*i > 0 && line[*i - 1] != ' ' && line[*i] != line[*i - 1])
		new_line[(*j)++] = ' ';
	new_line[(*j)++] = line[*i];
	if (line[*i + 1] && line[*i + 1] != ' ' && line[*i] != line[*i + 1])
		new_line[(*j)++] = ' ';
	(*i)++;
}
