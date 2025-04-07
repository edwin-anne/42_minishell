/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:11:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/25 17:39:30 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void add_args(t_cmd *cmd, char *arg)
{
	int i = 0;
	int j = 0;
	char **new_args;
	char **old_args;

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
	old_args = cmd->args;
	cmd->args = new_args;
	free(old_args);
	cmd->is_builtin = is_built_in(cmd->args);
}

void add_redir(t_redir **redir_list, t_token *token, t_redir_type type)
{
	t_redir *new_redir;
	t_redir *last;

	if (!token->next || token->next->type != WORD)
	{
		ft_fdprintf(2, "minishell: syntax error near unexpected token\n");
		return;
	}

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return;
	new_redir->type = type;
	new_redir->file = strdup(token->next->value);
	new_redir->limiter = (type == HEREDOC) ? strdup(token->next->value) : NULL;
	new_redir->fd = -1;
	new_redir->next = NULL;

	// Ajouter la redirection à la fin de la liste
	if (!(*redir_list))
		*redir_list = new_redir;
	else
	{
		last = *redir_list;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

void guess_redir(t_cmd *cmd, t_token *token)
{
	if (!cmd || !token)
		return;

	if (token->type == REDIR_IN)
		add_redir(&cmd->redir_in, token, INPUT_REDIR);
	else if (token->type == REDIR_OUT)
		add_redir(&cmd->redir_out, token, OUTPUT_REDIR);
	else if (token->type == APPEND)
		add_redir(&cmd->redir_out, token, APPEND_REDIR);
	else if (token->type == HERE_DOC)
		add_redir(&cmd->redir_in, token, HEREDOC);
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
				 token->type == APPEND || token->type == HERE_DOC)
		{
			guess_redir(current_cmd, token);
			if (token->next)
				token = token->next;
			else
				ft_fdprintf(2, "minishell: syntax error near unexpected token `newline'\n");
		}
		else if (token->type == WORD || token->type == ENV_VAR)
			add_args(current_cmd, token->value);
		token = token->next;
	}

	execute_here_doc_cmds(cmd_list);
	quote(cmd_list->args);
	execute_env_var(shell->env, cmd_list->args);
	interpret_quotes(cmd_list->args);
	return (cmd_list);
}
