/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:41:49 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/17 09:53:42 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_shell	*parsing(t_shell *shell, char *line, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	**line_splited;
	t_token	*token;

	line = pre_parsing(line);
	//debug_pre_parsing(line);
	line_splited = ft_split(line, ' ');
	free(line);
	token = tokenization(line_splited);
	free_char_array(line_splited);
	//view_token_struct(token);
	shell->cmds = create_cmd(token, shell);
	create_pipe(shell->cmds);
	free_tokens(token);
	print_cmd_list(shell->cmds);
	return (shell);
}
