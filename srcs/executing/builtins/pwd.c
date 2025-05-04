/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:46:58 by loribeir          #+#    #+#             */
/*   Updated: 2025/05/04 10:20:04 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

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
