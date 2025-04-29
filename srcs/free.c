/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:21:25 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 15:54:05 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	clean_heredoc_files(cmd);
	while (cmd)
	{
		tmp = cmd;
		free_cmds_next(cmd);
		cmd = cmd->next;
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
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
