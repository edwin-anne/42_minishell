/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:35:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/19 15:54:57 by lolq             ###   ########.fr       */
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
	while (1)
	{
		line = readline("$ ");
		if (!line)
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		parsing(shell, line, argc, argv);
		builtins_executing(shell, shell->cmds);
		find_executable(shell->cmds, shell->env);
		if (line[0] != '\0')
			add_history(line);
	}
	clear_history();
	rl_clear_history();
	return (0);
}

/**
 * LE PATH + FIND EXECUTABLE : 
 * shell->cmds->path = find_executable(shell->cmds, shell->env);
		ft_fdprintf(2, "%s\n", shell->cmds->path);
*/
