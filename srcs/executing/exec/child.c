/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:38:24 by lolq              #+#    #+#             */
/*   Updated: 2025/04/17 09:29:30 by lolq             ###   ########.fr       */
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
        print_cmd_list(cmds);
        handle_fork(shell, tmp);
        close_pipes(tmp);
        tmp = tmp->next;
    }
    return (FAIL);
}

void    handle_fork(t_shell *shell, t_cmd *cmd)
{
    pid_t   pid;

    if (builtins_parent(shell, cmd) != SUCCESS)
    {
        pid = fork();
        if (pid < 0)
            exit(1); // TODO: ne pas oublier de free la struct (edwin)
        if (pid == 0)
        {
            ft_dup(cmd);
            ft_dup_redir(cmd->redir_in, cmd->redir_out);
            exec_child(cmd, shell);
            exit(0);
        }
    }
    cmd->pid = pid; 
}
void exec_child(t_cmd *cmds, t_shell *shell)
{
    char    **env;
    
    env = env_char(shell);
    find_executable(cmds, shell->env);
    if (cmds->is_builtin == true)
        builtins_child(shell, cmds);
    else 
    {
        if (execve(cmds->path, cmds->args, env) == -1)
        {
            free_shell(shell);
            perror("execve failed");
            exit(EXIT_FAILURE);    
        }
        
    }
    free_char_array(env);
}

void    wait_children(t_shell *shell)
{
    t_cmd *tmp;
    int status;

    tmp = shell->cmds;
    while (tmp)
    {
        if (tmp->pid > 0)
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
