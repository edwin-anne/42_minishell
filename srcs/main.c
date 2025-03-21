/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:35:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/21 11:12:49 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executing.h"
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char    *line_copy;
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
		if (line[0] != '\0')
		{
			line_copy = ft_strdup(line);
			parsing(shell, line, argc, argv);
			builtins_executing(shell, shell->cmds);
			add_history(line_copy);
			free(line_copy);
		}
		else
			parsing(shell, line, argc, argv);
	}
	free_shell(shell);
	clear_history();
	rl_clear_history();
	return (0);
}

