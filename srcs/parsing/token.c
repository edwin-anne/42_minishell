/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:50:55 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/22 22:08:46 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*tokenization(char **line)
{
	int i;
	t_token *first = NULL;
	t_token *prev = NULL;
	t_token *new = NULL;

	i = 0;
	while (line[i] != NULL)
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return (NULL);
		new->value = strdup(line[i]);
		new->type = tokenization_set_type(line[i]);
		new->skip = 0;
		if (!new->value)
			return (free(new), NULL);
		new->next = NULL;
		new->prev = prev;
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