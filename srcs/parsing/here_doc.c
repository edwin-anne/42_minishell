/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:43:44 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/05/01 12:00:41 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*execute_here_doc(t_shell *shell, char *filepath, char *limiter)
{
	char	*limit_with_nl;
	int		fd;
	char	*result;

	(void)shell;
	limit_with_nl = ft_strjoin(limiter, "\n");
	if (!limit_with_nl)
		return (NULL);
	if (!open_here_doc_file(filepath, limit_with_nl, &fd))
		return (NULL);
	result = read_heredoc_lines(fd, limit_with_nl);
	free(limit_with_nl);
	close(fd);
	if (!result)
	{
		unlink(filepath);
		return (NULL);
	}
	return (filepath);
}

int	handle_here_doc(t_shell *shell, t_redir *redir, int *id_here_doc)
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
	if (execute_here_doc(shell, filepath, redir->limiter))
	{
		free(redir->file);
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

int	execute_here_doc_cmds(t_cmd *cmds, t_shell *shell)
{
	t_redir	*redir;
	int		id_here_doc;
	t_cmd	*cmds_orig;

	id_here_doc = 0;
	cmds_orig = cmds;
	while (cmds)
	{
		redir = cmds->redir_in;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (handle_here_doc(shell, redir, &id_here_doc))
				{
					clean_heredoc_files(cmds_orig);
					return (1);
				}
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
