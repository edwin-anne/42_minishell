/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:02:29 by lolq              #+#    #+#             */
/*   Updated: 2025/04/07 18:03:51 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handling_open(t_redir *redir, int flags, mode_t mode)
{
    if (!redir || !redir->file)
        return ;
    redir->fd = open(redir->file, flags, mode);
	if (redir->fd < 0)
	{
		perror(redir->file);
		redir->fd = -1;
	}
}

void   open_fds(t_cmd *cmds)
{
    t_cmd *tmp;

    tmp = cmds;
    while (tmp)
    {
        if (tmp->redir_in && tmp->redir_in->type != NO_REDIR)
            handling_open(tmp->redir_in, O_RDONLY, 0);
        if (tmp->redir_out && tmp->redir_out->type != NO_REDIR)
            handling_open(tmp->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        tmp = tmp->next;
    }
}