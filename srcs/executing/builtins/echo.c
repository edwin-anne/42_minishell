/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:02:15 by lolq              #+#    #+#             */
/*   Updated: 2025/04/30 13:57:06 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief: echo have to write arguments to minishell output.
 * And echo -n will not add a newline.
 */

int	ft_echo(t_shell *shell, t_cmd *cmds)
{
	char	**args;
	int		no_nl;
	int		i;

	no_nl = 0;
	i = 1;
	args = cmds->args;
	while (args[i] && echo_option(args[i]))
	{
		no_nl = 1;
		i++;
	}
	while (args[i])
	{
		if (args[i + 1] == NULL)
			ft_fdprintf(1, "%s", args[i]);
		else
			ft_fdprintf(1, "%s ", args[i]);
		i++;
	}
	if (no_nl == 0)
		ft_fdprintf(1, "\n");
	shell->exit_status = 0;
	return (SUCCESS);
}

int	echo_option(const char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-' || arg[1] == '\0')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}
