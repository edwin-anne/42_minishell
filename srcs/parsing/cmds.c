/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:11:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/06 08:57:09 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void add_args(t_cmd *cmd, char *arg)
{
	int	i;
	int	j;
	char **new_args;

	i = 0;
	j = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return;
	while (j < i)
	{
		new_args[j] = cmd->args[j];
		j++;
	}
	new_args[i] = strdup(arg);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	cmd->is_builtin = is_built_in(cmd->args);
}

void guess_redir(t_cmd *cmd, t_token *token)
{
	int	redir_type;

	if (!cmd || !token || !cmd->redir)
		return ;
	if (!token->type)
	{
		cmd->redir->type_in = NONE;
		return ;
	}
	if (token->type == REDIR_IN || token->type == REDIR_OUT || 
		token->type == APPEND || token->type == HEREDOC)
	{
		if (!token->next || token->next->type != WORD)
		{
			cmd->redir->type_in = NONE;
			return ;
		}
		redir_type = NONE;
		if (token->type == REDIR_IN)
			redir_type = FILE_REDIR;
		else if (token->type == REDIR_OUT)
			redir_type = FILE_REDIR;
		else if (token->type == APPEND)
			redir_type = APPEND_REDIR;
		else if (token->type == HEREDOC)
			redir_type = HERE_DOC;
		write_redir(cmd, token, redir_type);
	}
	else
		cmd->redir->type_in = NONE;
}

void write_redir(t_cmd *cmd, t_token *token, t_redir_type type)
{
	if (!cmd || !token || !cmd->redir || !token->next)
		return;
	
	cmd->redir->type_in = type;
	if (token->next->value)
		cmd->redir->file_in = strdup(token->next->value);
	else
		cmd->redir->file_in = NULL;
}

t_cmd *create_cmd(t_token *token, t_shell *shell)
{
	t_cmd *cmd_list = NULL;
	t_cmd *current_cmd = NULL;
	
	cmd_list = init_cmd();
	current_cmd = cmd_list;
	while (token)
	{
		if (!cmd_list)
		{
			cmd_list = init_cmd();
			current_cmd = cmd_list;
		}
		else if (token->type == PIPE)
		{
			current_cmd->next = init_cmd();
			current_cmd = current_cmd->next;
		}
		else if (token->type == REDIR_IN || token->type == REDIR_OUT || 
				token->type == APPEND || token->type == HEREDOC)
		{
			guess_redir(current_cmd, token);
			if (token->next)
				token = token->next;
			else
				printf("minishell: syntax error near unexpected token `newline'\n");
		}
		else if (token->type == WORD || token->type == ENV_VAR)
			add_args(current_cmd, token->value);
		token = token->next;
	}
	execute_here_doc_cmds(cmd_list);
	execute_env_var(shell->env, cmd_list->args);
	//quote(cmd_list->args);
	return (cmd_list);
}
