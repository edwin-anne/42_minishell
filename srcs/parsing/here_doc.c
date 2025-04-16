/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:43:44 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/16 11:40:10 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*execute_here_doc(char *filepath, char *limiter)
{
	char    *limit_with_nl;
	char    *line;
	int     fd;

	limit_with_nl = ft_strjoin(limiter, "\n");
	fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (!limit_with_nl || fd < 0)
	{
		ft_fdprintf(2, "minishell: erreur d'ouverture du fichier here_doc\n");
		free(limit_with_nl);
		return (NULL);
	}
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line
				|| ft_strncmp(line, limit_with_nl, ft_strlen(limit_with_nl)) == 0)
		{
			free(line);
			free(limit_with_nl);
			close(fd);
			return (filepath);
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(limit_with_nl);
	close(fd);
	return (NULL); // Ajout d'un return en cas d'erreur imprévue
}

void execute_here_doc_cmds(t_cmd *cmds)
{
    int id_here_doc;
    char *id_str;
    char *filepath;
    t_redir *redir;

    id_here_doc = 0;
    while (cmds != NULL)
    {
        redir = cmds->redir_in;
        while (redir != NULL)
        {
            if (redir->type == HEREDOC)
            {
                id_str = ft_itoa(id_here_doc);
                if (!id_str)
                    ft_fdprintf(2, "minishell: memory allocation error\n");
                    return;
                filepath = ft_strjoin("/tmp/minishell_here_doc_", id_str);
                free(id_str);
                if (!filepath)
                {
                    ft_fdprintf(2, "minishell: memory allocation error\n");
                    return;
                }
                if (execute_here_doc(filepath, redir->limiter))
                {
                    redir->file = ft_strdup(filepath);
                    if (!redir->file)
                    {
                        ft_fdprintf(2, "minishell: memory allocation error\n");
                        free(filepath);
                        return;
                    }
                    redir->type = INPUT_REDIR;
                    id_here_doc++;
                }
                free(filepath);
            }
            redir = redir->next;
        }
        cmds = cmds->next;
    }
}
