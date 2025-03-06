/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:43:44 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/02 12:47:48 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*execute_here_doc(char *filepath, char *limiter)
{
	char    *limit_with_nl;
	char    *line;
	int             fd;

	limit_with_nl = ft_strjoin(limiter, "\n");
	fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (!limit_with_nl || fd < 0)
			return (NULL);
	while (1)
	{
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
			if (!line
					|| ft_strncmp(line, limit_with_nl, ft_strlen(limit_with_nl)) == 0)
			{
					free(line);
					free(limit_with_nl);
					close (fd);
					return (filepath);
			}
			write(fd, line, ft_strlen(line));
			free(line);
	}
	free(limit_with_nl);
	close(fd);
}

void	execute_here_doc_cmds(t_cmd *cmds)
{
	int	id_here_doc;
	
	id_here_doc = 0;
	while (cmds != NULL)
	{
		if (cmds->redir && cmds->redir->type_in == HERE_DOC)
		{
			//TODO -> recuperer le limiter qui doit etre ajouter dans la struct
			debug_here_doc(ft_itoa(id_here_doc), "test");
			cmds->redir->file_in = execute_here_doc(ft_itoa(id_here_doc), "test");
			id_here_doc++;
		}
		cmds = cmds->next;
	}
}