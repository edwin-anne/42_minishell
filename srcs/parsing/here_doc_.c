/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:47:19 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 16:30:37 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

// void	handle_heredoc_child(t_shell *shell, char *limit_with_nl, int fd)
// {
// 	char	*line;

// 	setup_heredoc_signals();
// 	while (1)
// 	{
// 		ft_putstr_fd("> ", 1);
// 		line = get_next_line(0);
// 		if (!line || ft_strncmp(line, limit_with_nl,
// 				ft_strlen(limit_with_nl)) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		free(line);
// 	}
// 	free(limit_with_nl);
// 	free_shell(shell);
// 	close(fd);
// 	exit(0);
// }

// int	handle_heredoc_parent(pid_t pid, struct sigaction *old_int,
// 		struct sigaction *old_quit, char *limit_with_nl)
// {
// 	int	status;

// 	waitpid(pid, &status, 0);
// 	sigaction(SIGINT, old_int, NULL);
// 	sigaction(SIGQUIT, old_quit, NULL);
// 	free(limit_with_nl);
// 	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
// 		return (1);
// 	return (0);
// }

