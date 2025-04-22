/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:43:44 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/17 09:51:17 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	open_here_doc_file(char *filepath, char *limit_with_nl, int *fd)
{
	*fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (!limit_with_nl || *fd < 0)
	{
		free(limit_with_nl);
		ft_fdprintf(2, "minishell: erreur d'ouverture du fichier here_doc\n");
		return (0);
	}
	return (1);
}

char	*execute_here_doc(char *filepath, char *limiter)
{
	char	*limit_with_nl;
	char	*line;
	int		fd;

	limit_with_nl = ft_strjoin(limiter, "\n");
	if (!open_here_doc_file(filepath, limit_with_nl, &fd))
		return (NULL);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, limit_with_nl,
				ft_strlen(limit_with_nl)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(limit_with_nl);
	close(fd);
	return (filepath);
}

static int	handle_here_doc(t_redir *redir, int *id_here_doc)
{
	char	*id_str;
	char	*filepath;

	id_str = ft_itoa(*id_here_doc);
	if (!id_str)
		return (ft_fdprintf(2, "minishell: memory allocation error\n"), 1);
	filepath = ft_strjoin("/tmp/minishell_here_doc_", id_str);
	free(id_str);
	if (!filepath)
		return (ft_fdprintf(2, "minishell: memory allocation error\n"), 1);
	if (execute_here_doc(filepath, redir->limiter))
	{
		redir->file = ft_strdup(filepath);
		if (!redir->file)
		{
			free(filepath);
			return (ft_fdprintf(2, "minishell: memory allocation error\n"), 1);
		}
		redir->type = INPUT_REDIR;
		(*id_here_doc)++;
	}
	free(filepath);
	return (0);
}

int	execute_here_doc_cmds(t_cmd *cmds)
{
	t_redir	*redir;
	int		id_here_doc;

	id_here_doc = 0;
	while (cmds)
	{
		redir = cmds->redir_in;
		while (redir)
		{
			if (redir->type == HEREDOC)
				if (handle_here_doc(redir, &id_here_doc))
					return (1);
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
