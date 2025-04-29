/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:01:15 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 17:08:41 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_getexitcode(t_shell *shell)
{
	char	*result;

	result = ft_itoa(shell->exit_status);
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
