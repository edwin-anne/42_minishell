/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:55:57 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 10:57:46 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static	t_redir	*create_new_redir(t_token *token, t_redir_type type)
{
	t_redir	*new_redir;
	char	*temp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	temp = ft_strdup(token->next->value);
	if (!temp)
		return (free(new_redir), NULL);
	new_redir->file = remove_quotes(temp);
	free(temp);
	if (!new_redir->file)
		return (free(new_redir), NULL);
	new_redir->fd = -1;
	new_redir->next = NULL;
	return (new_redir);
}

static int	setup_heredoc(t_redir *redir, t_token *token)
{
	if (redir->type == HEREDOC)
	{
		redir->limiter = ft_strdup(token->next->value);
		if (!redir->limiter)
			return (free(redir->file), free(redir), 0);
	}
	else
		redir->limiter = NULL;
	return (1);
}

static void	append_redir(t_redir **redir_list, t_redir *new_redir)
{
	t_redir	*last;

	if (!(*redir_list))
		*redir_list = new_redir;
	else
	{
		last = *redir_list;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

int	add_redir(t_redir **redir_list, t_token *token, t_redir_type type)
{
	t_redir	*new_redir;

	new_redir = create_new_redir(token, type);
	if (!new_redir)
		return (0);
	if (!setup_heredoc(new_redir, token))
		return (0);
	append_redir(redir_list, new_redir);
	return (1);
}
