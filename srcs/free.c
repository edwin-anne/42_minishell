/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:21:25 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 13:53:13 by Edwin ANNE       ###   ########.fr       */
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

    if (!cmd)
        return;
    while (cmd)
    {
        tmp = cmd;
        if (cmd->args)
        {
            int i = 0;
            while (cmd->args[i])
            {
                if (cmd->args[i])
                    free(cmd->args[i]);
                i++;
            }
            free(cmd->args);
            cmd->args = NULL;
        }

        cmd->path = NULL;
        if (cmd->redir_in)
        {
            free_redir_list(cmd->redir_in);
            cmd->redir_in = NULL;
        }
        if (cmd->redir_out)
        {
            free_redir_list(cmd->redir_out);
            cmd->redir_out = NULL;
        }
        if (cmd->pipe)
        {
            free(cmd->pipe);
            cmd->pipe = NULL;
        }
        cmd = cmd->next;
        if (tmp)
        {
            free(tmp);
            tmp = NULL;
        }
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
