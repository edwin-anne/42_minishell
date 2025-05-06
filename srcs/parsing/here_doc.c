/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:43:44 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/05/05 16:30:26 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	process_heredoc_in_child(t_shell *shell,
	char *filepath,
	char *limit_with_nl)
{
	int		fd;
	char	*result;

	if (!open_here_doc_file(filepath, limit_with_nl, &fd))
	{
		free(limit_with_nl);
		free_shell(shell);
		free(filepath);
		exit(EXIT_FAILURE);
	}
	result = read_heredoc_lines(fd, limit_with_nl);
	free(limit_with_nl);
	close(fd);
	if (!result)
	{
		unlink(filepath);
		free(filepath);
		free_shell(shell);
		exit(130);
	}
	free(filepath);
	free_shell(shell);
	exit(EXIT_SUCCESS);
}

char	*execute_here_doc(t_shell *shell, char *filepath, char *limiter)
{
	char	*limit_with_nl;
	pid_t	pid;
	int		status;

	g_heredoc_interrupted = 0;
	(void)shell;
	limit_with_nl = ft_strjoin(limiter, "\n");
	if (!limit_with_nl)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (free(limit_with_nl), \
			ft_fdprintf(2, "minishell: fork error\n"), NULL);
	if (pid == 0)
		process_heredoc_in_child(shell, filepath, limit_with_nl);
	free(limit_with_nl);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_heredoc_interrupted = 1;
		return (NULL);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (NULL);
	return (filepath);
}

int	handle_here_doc(t_shell *shell, t_redir *redir, int *id_here_doc)
{
	char	*id_str;
	char	*filepath;
	char	*result;

	id_str = ft_itoa(*id_here_doc);
	if (!id_str)
		return (ft_fdprintf(2, "minishell: memory allocation error\n"), 1);
	filepath = ft_strjoin("/tmp/minishell_here_doc_", id_str);
	free(id_str);
	if (!filepath)
		return (ft_fdprintf(2, "minishell: memory allocation error\n"), 1);
	result = execute_here_doc(shell, filepath, redir->limiter);
	if (result)
	{
		free(redir->file);
		redir->file = ft_strdup(filepath);
		if (!redir->file)
			return (free(filepath), \
					ft_fdprintf(2, "minishell: memory allocation error\n"), 1);
		redir->type = INPUT_REDIR;
		(*id_here_doc)++;
		return (free(filepath), 0);
	}
	else
		return (free(filepath), 1);
}

int	execute_here_doc_cmds(t_cmd *cmds, t_shell *shell)
{
	t_redir	*redir;
	int		id_here_doc;
	t_cmd	*cmds_orig;

	id_here_doc = 0;
	g_heredoc_interrupted = 0;
	cmds_orig = cmds;
	while (cmds && !g_heredoc_interrupted)
	{
		redir = cmds->redir_in;
		while (redir && !g_heredoc_interrupted)
		{
			if (redir->type == HEREDOC)
			{
				if (handle_here_doc(shell, redir, &id_here_doc))
					return (clean_heredoc_files(cmds_orig), 1);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	if (g_heredoc_interrupted)
		return (1);
	return (0);
}
