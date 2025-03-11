/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:21:25 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/09 13:57:00 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->file_in != NULL)
		free(redir->file_in);
	if (redir->limiter_here_doc != NULL)
		free(redir->limiter_here_doc);
	if (redir->file_out != NULL)
		free(redir->file_out);
	if (redir)
		free(redir);
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	while (cmd)
	{
		tmp = cmd;
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		free(cmd->path);
		if (cmd->redir)
			free_redir(cmd->redir);
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		free(env->key);
		free(env->value);
		env = env->next;
		free(tmp);
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_env(shell->env);
	free_cmds(shell->cmds);
	free(shell);
}

void	free_char_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
