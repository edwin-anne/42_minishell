/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:35:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/27 14:03:32 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executing.h"
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	*shell;

	using_history();
	rl_initialize();
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->env = copy_env(envp);
	shell->cmds = NULL;
	shell->exit_status = 0;
	init_signals(shell);
	while (1)
	{
		line = readline("$ ");
		if (!line)
		{
			ft_putstr_fd("\n", 1);
			break;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			parsing(shell, line, argc, argv);
			if (shell->cmds)
			{
				executing(shell);
				free_cmds(shell->cmds);
				shell->cmds = NULL;
			}
		}
		free(line);
	}
	free_shell(shell);
	clear_history();
	rl_clear_history();
	return (0);
}

