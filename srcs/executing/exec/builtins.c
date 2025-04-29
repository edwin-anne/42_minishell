/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:14:13 by lolq              #+#    #+#             */
/*   Updated: 2025/04/28 12:08:45 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief : builtins exec will check which builtins is called and execute the
 * correct ones.
 * if the cmd is inside a pipe or redir, then the cmd should not execute inside
 * the parent.
 */

int	builtins_child(t_shell *shell, t_cmd *cmds)
{
	char	**args;

	args = cmds->args;
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(cmds));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(shell));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(shell, cmds));
	else
		return (FAIL);
	return (shell->exit_status);
}

int	builtins_parent(t_shell *shell, t_cmd *cmds)
{
	char	**args;

	args = cmds->args;
	if (cmds->pipe != NULL || cmds->pipe_prev != NULL)
		return (FAIL);
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(shell, cmds));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(shell, cmds->args), shell->exit_status);
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(shell, cmds), shell->exit_status);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(shell, cmds, shell->env));
	else
		return (FAIL);
	return (shell->exit_status);
}
