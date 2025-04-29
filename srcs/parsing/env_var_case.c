/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:01:15 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 15:42:22 by Edwin ANNE       ###   ########.fr       */
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

char	*ft_getexitcode(t_shell *shell)
{
	char	*result;
	char	exit_status[12];

	snprintf(exit_status, sizeof(exit_status), "%d", shell->exit_status);
	result = ft_strdup(exit_status);
	return (result);
}

void	remove_empty_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
		{
			args[j] = args[i];
			j++;
		}
		else
			free(args[i]);
		i++;
	}
	args[j] = NULL;
}
