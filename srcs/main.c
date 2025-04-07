/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:35:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/05 13:08:44 by lolq             ###   ########.fr       */
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
	shell->env = copy_env(envp);
	init_signals(shell);
	while (1)
	{
		line = readline("$ ");
		if (!line)
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			parsing(shell, line, argc, argv);
			executing(shell);
			free_cmds(shell->cmds);
		}
		free(line);
	}
	free_shell(shell);
	clear_history();
	rl_clear_history();
	return (0);
}

