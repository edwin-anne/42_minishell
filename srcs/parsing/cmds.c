/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:11:28 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/05/06 09:44:01 by Edwin ANNE       ###   ########.fr       */
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
		return (free(new_args));
	new_args[i + 1] = NULL;
	old_args = cmd->args;
	cmd->args = new_args;
	free(old_args);
	cmd->is_builtin = is_built_in(cmd->args);
}

void	guess_redir(t_shell *shell, t_cmd *cmd, t_token *token)
{
	if (!cmd || !token)
		return ;
	if (token->type == REDIR_IN)
		add_redir(&cmd->redir_in, token, INPUT_REDIR, shell);
	else if (token->type == REDIR_OUT)
		add_redir(&cmd->redir_out, token, OUTPUT_REDIR, shell);
	else if (token->type == APPEND)
		add_redir(&cmd->redir_out, token, APPEND_REDIR, shell);
	else if (token->type == HERE_DOC)
		add_redir(&cmd->redir_in, token, HEREDOC, shell);
}

int	process_command(t_cmd *cmd_list, t_shell *shell, int i)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (!quote(tmp->args, i))
		{
			ft_fdprintf(2,
				"minishell: syntax error near unexpected token\n");
			shell->exit_status = 2;
			return (0);
		}
		if (!interpret_parentheses(tmp->args))
		{
			ft_fdprintf(2,
				"minishell: syntax error near unexpected token `('\n");
			shell->exit_status = 2;
			return (0);
		}
		execute_env_var(shell, tmp->args);
		interpret_quotes(tmp->args);
		tmp = tmp->next;
	}
	return (1);
}

int	process_token(t_shell *shell, t_token *token, t_cmd *current_cmd)
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
		guess_redir(shell, current_cmd, token);
		token->next->skip = 1;
	}
	else if ((token->type == WORD || token->type == ENV_VAR) && !token->skip)
		add_args(current_cmd, token->value);
	return (1);
}

t_cmd	*create_cmd(t_token *token, t_shell *shell, int i)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	cmd_list = init_cmd();
	current_cmd = cmd_list;
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->next || token->next->type == PIPE)
				return (ft_fdprintf(2, SYNTAX_ERR_PIPE),
					free_cmds(cmd_list), NULL);
			current_cmd->next = init_cmd();
			current_cmd = current_cmd->next;
		}
		else
		{
			if (process_token(shell, token, current_cmd) == 0)
				return (free_cmds(cmd_list), NULL);
		}
		token = token->next;
	}
	if (!process_command(cmd_list, shell, i))
		return (free_cmds(cmd_list), NULL);
	return (cmd_list);
}
