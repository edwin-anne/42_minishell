/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:56:19 by lolq              #+#    #+#             */
/*   Updated: 2025/04/28 12:04:40 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief Useful & necessary functions to make the child.c file working. 
 */

char	**env_char(t_shell *shell)
{
	char	**result;
	char	*key_eq;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = shell->env;
	result = malloc(sizeof(char *) * (env_len(tmp) + 1));
	if (!result)
		return (NULL);
	while (tmp)
	{
		key_eq = ft_strjoin(tmp->key, "=");
		if (!key_eq)
			return (free_char_array(result), NULL);
		result[i] = ft_strjoin(key_eq, tmp->value);
		free(key_eq);
		if (!result[i])
			return (free_char_array(result), NULL);
		tmp = tmp->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	env_len(t_env *env)
{
	t_env	*tmp;
	int		res;

	res = 0;
	tmp = env;
	while (tmp)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}
