/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:41:49 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/05/01 10:30:57 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_shell	*parsing(t_shell *shell, char *line, int argc, char **argv)
{
	char	**line_splited;
	t_token	*token;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	line = pre_parsing(line);
	line_splited = ft_split_sh(line, ' ');
	free(line);
	token = tokenization(line_splited, i);
	free_char_array(line_splited);
	shell->cmds = create_cmd(token, shell);
	if (shell->cmds)
		create_pipe(shell->cmds);
	free_tokens(token);
	return (shell);
}
