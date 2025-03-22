/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:38:24 by lolq              #+#    #+#             */
/*   Updated: 2025/03/22 17:23:24 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief: handles the creation and execution of child processes for cmd exec.
 *  - create child processes for each cmd in the linked list. 
 *  - exec a cmd in a child process, handling if it's a built-ins or not. 
 */

int create_child(t_shell *shell, t_cmd *cmds)
{
    t_cmd   *tmp;
    pid_t   pid;
    
    tmp = cmds;
    while (tmp != NULL)
    {
        pid = fork();
        if (pid < 0)
            exit(1); // TODO: ne pas oublier de free la struct (edwin)
        if (pid == 0)
        {
            // Child process
            printf("Child process for command: %s\n", tmp->args[0]);
            exec_child(shell);
            exit(0); // Quit child after executing
        }
        // Parent continues
        tmp->pid = pid;
        printf("Parent created child pid: %d for cmd: %s\n", pid, tmp->args[0]);
        tmp = tmp->next;
    }
    return (FAIL);
}

void exec_child(t_shell *shell)
{
    char    **env;

    env = env_char(shell);
    find_executable(shell->cmds, shell->env);
    if (shell->cmds->is_builtin == true)
        builtins_executing(shell, shell->cmds);
    else 
    {
        if (execve(shell->cmds->path, shell->cmds->args, env) == -1)
        {
            perror("execve failed");
            exit(EXIT_FAILURE);    
        }
    }
    free_char_array(env);
}

