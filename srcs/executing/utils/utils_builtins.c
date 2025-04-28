/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:54:39 by loribeir          #+#    #+#             */
/*   Updated: 2025/04/28 12:01:08 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "minishell.h"

/**
 * @brief Useful & necessary functions to make builtins working.
 */

t_env	*search_lst(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	free_node_env(t_env *env)
{
	if (env)
	{
		free(env->key);
		free(env->value);
		free(env);
	}
}

int	ft_strcharcmp(char *str, char comp)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == comp)
			i++;
		else
			return (FAIL);
	}
	return (SUCCESS);
}

int	ft_constcmp(char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

t_env	*add_var_back(t_env *env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new_var;

	if (!env)
		return (NULL);
	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	new_var->key = key;
	new_var->value = value;
	new_var->next = NULL;
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_var;
	return (env);
}
