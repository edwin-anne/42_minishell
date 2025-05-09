/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 08:53:09 by lolq              #+#    #+#             */
/*   Updated: 2025/05/04 10:19:57 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	ft_exit(t_shell *shell, t_cmd *cmds)
{
	int		exit_code;
	char	**args;
	long	nb;

	args = cmds->args;
	if (!args[1])
		return (free_shell(shell), exit(0), (void)0);
	ft_fdprintf(1, "exit\n");
	nb = ft_atol(args[1]);
	if (args[2])
	{
		ft_fdprintf(2, "bash: exit: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}
	if (!is_arg_nb(args[1]))
	{
		ft_fdprintf(2, "bash: exit: %s: numeric argument required\n", args[1]);
		free_shell(shell);
		exit(2);
	}
	exit_code = (int)((nb % 256 + 256) % 256);
	free_shell(shell);
	exit(exit_code);
}

int	is_arg_nb(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}
