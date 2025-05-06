/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:47:19 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/05/05 16:19:47 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	g_heredoc_interrupted = 0;

static void	handle_heredoc_signal(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(1, "\n", 1);
	close(0);
}

void	clean_heredoc_files(t_cmd *cmds)
{
	t_redir	*redir;
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		redir = current->redir_in;
		while (redir)
		{
			if (redir->type == INPUT_REDIR && redir->file
				&& ft_strncmp(redir->file, "/tmp/minishell_here_doc_", 24) == 0)
			{
				unlink(redir->file);
			}
			redir = redir->next;
		}
		current = current->next;
	}
}

int	open_here_doc_file(char *filepath, char *limit_with_nl, int *fd)
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

char	*read_heredoc_lines(int fd, char *limit_with_nl)
{
	char	*line;
	void	(*old_sigint)(int);

	old_sigint = signal(SIGINT, handle_heredoc_signal);
	while (!g_heredoc_interrupted)
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
	signal(SIGINT, old_sigint);
	if (g_heredoc_interrupted)
		return (NULL);
	return ("success");
}
