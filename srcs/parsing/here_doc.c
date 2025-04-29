/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:43:44 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 16:27:07 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <features.h>

static int	g_heredoc_interrupted;

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

void	setup_heredoc_signals(struct sigaction *old_int, struct sigaction *old_quit)
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

char	*execute_here_doc(t_shell *shell, char *filepath, char *limiter)
{
	char				*limit_with_nl;
	int					fd;
	struct sigaction	old_int;
	struct sigaction	old_quit;
	char				*result;

	(void)shell;
	limit_with_nl = ft_strjoin(limiter, "\n");
	if (!limit_with_nl)
		return (NULL);
	if (!open_here_doc_file(filepath, limit_with_nl, &fd))
		return (NULL);
	setup_heredoc_signals(&old_int, &old_quit);
	result = read_heredoc_lines(fd, limit_with_nl);
	sigaction(SIGINT, &old_int, NULL);
	sigaction(SIGQUIT, &old_quit, NULL);
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
				if (handle_here_doc(shell, redir, &id_here_doc))
				{
					clean_heredoc_files(cmds_orig);
					return (1);
				}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
