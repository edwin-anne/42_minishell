/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:01:15 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/22 11:55:44 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_getpid(void)
{
	pid_t	pid;
	char	*result;
	char	pid_str[12];

	pid = getpid();
	snprintf(pid_str, sizeof(pid_str), "%d", pid);
	result = ft_strdup(pid_str);
	return (result);
}

/* TODO -> get exit status with struct t_shell */
char	*ft_getexitcode(void)
{
	char	*result;
	char	exit_status[12];

	snprintf(exit_status, sizeof(exit_status), "%d", 0);
	result = ft_strdup(exit_status);
	return (result);
}
