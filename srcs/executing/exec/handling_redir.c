/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:29:15 by lolq              #+#    #+#             */
/*   Updated: 2025/04/26 15:03:48 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void    redir_error(char *file)
{
    if (errno == EACCES)
        ft_fdprintf(2, "minishell: %s: Permission denied\n", file);
    else
        ft_fdprintf(2, "minishell: %s: No such file or directory\n", file);
}     
int    check_redir_in(t_redir *redir_in)
{
    t_redir *tmp;
    int last_fd;

    last_fd = -1;
    tmp = redir_in;
    while (tmp)
    {
        if (tmp->type == INPUT_REDIR || tmp->type == HEREDOC)
        {
            if (last_fd >= 0)
                close(last_fd);
            tmp->fd = open(tmp->file, O_RDONLY);
            if (tmp->fd < 0)
            {
                redir_error(tmp->file);
                return (-1);
            }
            last_fd = tmp->fd;
        }
        tmp = tmp->next;
    }
    return (last_fd);
}

int    check_redir_out(t_redir *redir_out)
{
    t_redir *tmp;
    int     last_fd;
    
    last_fd = -1;
    tmp = redir_out;
    while (tmp)
    {
        if (last_fd >= 0)
                close(tmp->fd);
        if (tmp->type == APPEND_REDIR)
            tmp->fd = open(tmp->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
        else if (tmp->type == OUTPUT_REDIR)
            tmp->fd = open(tmp->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        else
            tmp->fd = -1;
        if (tmp->fd < 0)
            return (redir_error(tmp->file), -1);
        last_fd = tmp->fd;
        tmp = tmp->next;
    }
    return(last_fd);
}

void    ft_dup_redir(t_redir *in, t_redir *out)
{
    int redir_in;
    int redir_out;

    if (in == NULL)
        redir_in = -1;
    else 
        redir_in = check_redir_in(in);
    if (out == NULL)
        redir_out = -1;
    else 
        redir_out = check_redir_out(out);
    
    if (redir_in > 0)
    {
        dup2(redir_in, STDIN_FILENO);
        close(redir_in);
    }
    if (redir_out > 0)
    {
        dup2(redir_out, STDOUT_FILENO);
        close(redir_out);
    }
}
