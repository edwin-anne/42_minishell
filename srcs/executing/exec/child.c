/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:38:24 by lolq              #+#    #+#             */
/*   Updated: 2025/04/26 15:19:40 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

/**
 * @brief: handles the creation and execution of child processes for cmd exec.
 *  - create child processes for each cmd in the linked list. 
 *  - exec a cmd in a child process, handling if it's a built-ins or not.
 *  - wait for all child processes to finish and update the exit status.
 */

int create_child(t_shell *shell, t_cmd *cmds)
{
    t_cmd   *tmp;
    
    tmp = cmds;
    while (tmp)
    {
        open_pipes(shell, tmp);
        handle_fork(shell, tmp);
        close_pipes(tmp);
        tmp = tmp->next;
    }
    return (FAIL);
}

void exec_child(t_cmd *cmds, t_shell *shell)
{
    char    **env;
    int     error;

    env = env_char(shell);
    find_executable(shell->cmds, shell->env);
    if (cmds->is_builtin == true)
    {
        builtins_child(shell, cmds);
        free_char_array(env);
        exit(shell->exit_status);
    }
    else 
    {
        error = exec_error(shell, cmds);
        if (error)
        {
            free_shell(shell);
            free_char_array(env);
            exit(shell->exit_status);
        }
        if (execve(cmds->path, cmds->args, env) == -1)
        {
            free_shell(shell);
            free_char_array(env);
            perror("execve failed");
            exit(EXIT_FAILURE);    
        }
    }
    free_shell(shell);
    free_char_array(env);
}

void    wait_children(t_shell *shell)
{
    int     status;
    t_cmd   *tmp;

    status = 0;
    tmp = shell->cmds;
    while (tmp)
    {
        if (tmp->has_child && tmp->pid > 0)
        {
            waitpid(tmp->pid, &status, 0);
            if (WIFEXITED(status))
                shell->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                shell->exit_status = 128 + WTERMSIG(status);
        }
        tmp = tmp->next;
    }
}
