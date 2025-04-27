/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:11:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/27 14:15:23 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_args(t_cmd *cmd, char *arg)
{
	int		i;
	int		j;
	char	**new_args;
	char	**old_args;

	i = 0;
	j = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	while (j < i)
	{
		new_args[j] = cmd->args[j];
		j++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
	{
		free(new_args);
		return;
	}
	new_args[i + 1] = '\0';
	old_args = cmd->args;
	cmd->args = new_args;
	free(old_args);
	cmd->is_builtin = is_built_in(cmd->args);
}

int	add_redir(t_redir **redir_list, t_token *token, t_redir_type type)
{
	t_redir	*new_redir;
	t_redir	*last;
	char	*temp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (0);
	new_redir->type = type;
	temp = ft_strdup(token->next->value);
	if (!temp)
	{
		free(new_redir);
		return (0);
	}
	new_redir->file = remove_quotes(temp);
	free(temp);
	if (!new_redir->file)
	{
		free(new_redir);
		return (0);
	}
	if (type == HEREDOC)
	{
		new_redir->limiter = ft_strdup(token->next->value);
		if (!new_redir->limiter)
		{
			free(new_redir->file);
			free(new_redir);
			return (0);
		}
	}
	else
		new_redir->limiter = NULL;
	new_redir->fd = -1;
	new_redir->next = NULL;
	if (!(*redir_list))
		*redir_list = new_redir;
	else
	{
		last = *redir_list;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
	return (1);
}

void	guess_redir(t_cmd *cmd, t_token *token)
{
	if (!cmd || !token)
		return ;
	if (token->type == REDIR_IN)
		add_redir(&cmd->redir_in, token, INPUT_REDIR);
	else if (token->type == REDIR_OUT)
		add_redir(&cmd->redir_out, token, OUTPUT_REDIR);
	else if (token->type == APPEND)
		add_redir(&cmd->redir_out, token, APPEND_REDIR);
	else if (token->type == HERE_DOC)
		add_redir(&cmd->redir_in, token, HEREDOC);
}

void	process_command(t_cmd *cmd_list, t_shell *shell)
{
	execute_here_doc_cmds(cmd_list);
	quote(cmd_list->args);
	execute_env_var(shell, cmd_list->args);
	interpret_quotes(cmd_list->args);
	interpret_parentheses(cmd_list->args);
}

int	process_token(t_token *token, t_cmd *current_cmd)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND || token->type == HERE_DOC)
	{
		if (!token->next)
		{
			ft_fdprintf(2,
				"minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}
		guess_redir(current_cmd, token);
		token->next->skip = 1;
	}
	else if ((token->type == WORD || token->type == ENV_VAR) && !token->skip)
		add_args(current_cmd, token->value);
	return (1);
}

t_cmd	*create_cmd(t_token *token, t_shell *shell)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

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
			if (!token->next)
			{
				ft_fdprintf(2, "minishell: syntax error near unexpected token `|'\n");
				return (free_cmds(cmd_list), NULL);
			}
			current_cmd->next = init_cmd();
			current_cmd = current_cmd->next;
		}
		else
		{
			if (process_token(token, current_cmd) == 0)
				return (free_cmds(cmd_list), NULL);
		}
		token = token->next;
	}
	return (process_command(cmd_list, shell), cmd_list);
}
