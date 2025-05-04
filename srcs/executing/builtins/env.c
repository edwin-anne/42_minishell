/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:12:37 by loribeir          #+#    #+#             */
/*   Updated: 2025/05/04 10:19:51 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	ft_env(t_shell *shell, t_cmd *cmds)
{
	t_env	*current;

	current = shell->env;
	if (cmds->args[1])
	{
		if (cmds->args[1])
		{
			ft_fdprintf(2, "env: '%s': No such file or directory\n",
				cmds->args[1]);
			shell->exit_status = 127;
			return (FAIL);
		}
	}
	shell->exit_status = 0;
	while (current)
	{
		if (current->value)
			ft_fdprintf(1, "%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (SUCCESS);
}
