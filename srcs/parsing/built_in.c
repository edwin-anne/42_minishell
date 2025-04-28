/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:53:00 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 12:06:47 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <string.h>

bool	is_built_in(char **cmds)
{
	if (!cmds || !cmds[0])
		return (false);
	if (ft_strcmp(cmds[0], "echo") == 0)
		return (true);
	if (ft_strcmp(cmds[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmds[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(cmds[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmds[0], "unset") == 0)
		return (true);
	if (ft_strcmp(cmds[0], "env") == 0)
		return (true);
	if (ft_strcmp(cmds[0], "exit") == 0)
		return (true);
	return (false);
}
