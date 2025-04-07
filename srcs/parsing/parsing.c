/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:41:49 by Edwin ANNE        #+#    #+#             *//*   Updated: 2025/02/27 20:25:32 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_shell	*parsing(t_shell *shell, char *line, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	**line_splited;
	t_token	*token;

	/*######	PRE PARSING 	######*/
	line = pre_parsing(line);
	debug_pre_parsing(line);
	/*######	TOKENISATION	######*/
	line_splited = ft_split(line, ' ');
	free(line);
	token = tokenization(line_splited);
	free_char_array(line_splited);
	view_token_struct(token);
	/*######	CMD 	######*/
	shell->cmds = create_cmd(token, shell);
	/*######	PIPE 	######*/
	create_pipe(shell->cmds);
	free_tokens(token);
	print_cmd_list(shell->cmds);
	return (shell);
}
