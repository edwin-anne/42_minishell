/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:47:19 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 16:42:15 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	g_heredoc_interrupted;

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

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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

void	setup_heredoc_signals(struct sigaction *old_int,
								struct sigaction *old_quit)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigaction(SIGINT, NULL, old_int);
	sigaction(SIGQUIT, NULL, old_quit);
	sa_int.sa_handler = handle_heredoc_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

char	*read_heredoc_lines(int fd, char *limit_with_nl)
{
	char	*line;

	g_heredoc_interrupted = 0;
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
	if (g_heredoc_interrupted)
		return (NULL);
	return ("success");
}
