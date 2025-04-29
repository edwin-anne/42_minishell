/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:50:55 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 18:56:34 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_token(char *line_content, t_token *prev)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = strdup(line_content);
	if (!new->value)
		return (free(new), NULL);
	new->type = tokenization_set_type(line_content);
	new->skip = 0;
	new->next = NULL;
	new->prev = prev;
	return (new);
}

t_token	*tokenization(char **line, int i)
{
	t_token	*first;
	t_token	*prev;
	t_token	*new;

	first = NULL;
	prev = NULL;
	while (line[i] != NULL)
	{
		new = create_token(line[i], prev);
		if (!new)
			return (NULL);
		if (!first)
		{
			first = new;
			prev = first;
		}
		else
		{
			prev->next = new;
			prev = new;
		}
		i++;
	}
	return (first);
}

t_token_type	tokenization_set_type(char *word)
{
	if (!word)
		return (WORD);
	if (word[0] == '\'' || word[0] == '"')
		return (WORD);
	if (ft_strcmp(word, "|") == 0)
		return (PIPE);
	if (ft_strcmp(word, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(word, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(word, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(word, "<<") == 0)
		return (HERE_DOC);
	if (word[0] == '$' && strlen(word) > 1)
		return (ENV_VAR);
	return (WORD);
}
