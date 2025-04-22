/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:21:25 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/16 12:00:45 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_redir_list(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        tmp = redir;
        if (redir->file)
            free(redir->file);
        if (redir->limiter)
            free(redir->limiter);
        redir = redir->next;
        free(tmp);
    }
}

void free_cmds(t_cmd *cmd)
{
    t_cmd *tmp;
    int i;

    while (cmd)
    {
        tmp = cmd;
        if (cmd->args)
        {
            i = 0;
            while (cmd->args[i])
            {
                free(cmd->args[i]);
                i++;
            }
            free(cmd->args);
        }

        if (cmd->path)
            free(cmd->path);
        if (cmd->redir_in)
            free_redir_list(cmd->redir_in);
        if (cmd->redir_out)
            free_redir_list(cmd->redir_out);
        cmd = cmd->next;
        free(tmp);
    }
}

void free_env(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env;
        free(env->key);
        free(env->value);
        env = env->next;
        free(tmp);
    }
}

void free_shell(t_shell *shell)
{
    if (!shell)
        return;
    free_env(shell->env);
    free_cmds(shell->cmds);
    free(shell);
}

void free_char_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i] != NULL)
    {
        free(array[i]);
        i++;
    }
    free(array);
}
