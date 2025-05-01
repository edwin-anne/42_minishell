/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:35:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/05/01 08:55:47 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executing.h"
#include "minishell.h"

void	init(t_shell **shell, char **envp)
{
	*shell = malloc(sizeof(t_shell));
	if (!*shell)
		exit(1);
	using_history();
	(*shell)->env = copy_env(envp);
	(*shell)->cmds = NULL;
	(*shell)->exit_status = 0;
	init_signals();
}

void	new_line(char *line, t_shell *shell, int argc, char **argv)
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	*shell;

	shell = NULL;
	init(&shell, envp);
	while (1)
	{
		line = readline("$ ");
		if (!line)
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		if (line[0] != '\0')
			new_line(line, shell, argc, argv);
		free(line);
	}
	free_shell(shell);
	clear_history();
	rl_clear_history();
	return (0);
}
