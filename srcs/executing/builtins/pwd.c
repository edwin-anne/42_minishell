/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:46:58 by loribeir          #+#    #+#             */
/*   Updated: 2025/04/28 11:49:14 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief: pwd return the working directory name.
 */
int	ft_pwd(t_shell *shell)
{
	char	*path;

	path = getcwd(0, 0);
	if (!path)
	{
		ft_fdprintf(2, "pwd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory\n");
		shell->exit_status = 1;
		return (FAIL);
	}
	else
		ft_fdprintf(1, "%s\n", path);
	free(path);
	shell->exit_status = 0;
	return (SUCCESS);
}
