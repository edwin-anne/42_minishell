/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:35:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/11 10:35:04 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	shell->env = copy_env(envp);
	print_env_list(shell->env);
	while (1)
	{
		line = readline("$ ");
		if (!line)
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
		parsing(shell, line, argc, argv);
		//Tu peux appeller ta fonction executing ici
		//Avec le t_shell *shell qui contiendra
		//ENV + la commande parser
		// if (shell->cmds->args[0][0] == '^')
		// {
		// 	rl_clear_history();
		// 	free_shell(shell);
		// 	exit(0);
		// }
		// else
		// free_cmds(shell->cmds);
		if (line[0] != '\0')
			add_history(line);
		free(line);
	}
	return (0);
}