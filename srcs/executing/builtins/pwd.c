/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:46:58 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/13 18:38:39 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief : Print Working Directory. 
 * The function should display the absolute path of the current directory.
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
