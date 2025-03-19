/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:46:58 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/19 10:35:19 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief : pwd return the working directory name.
 */

int    ft_pwd(void)
{
	char    *path;

	path = getcwd(0, 0);
	if (!path)
	{
		ft_fdprintf(1, "pwd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n");
		return (FAIL);
	}
	else
		ft_fdprintf(1, "%s\n", path);
	free(path);
	return (SUCCESS);
}
