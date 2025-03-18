/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:41:45 by lolq              #+#    #+#             */
/*   Updated: 2025/03/18 13:51:33 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief Implement the cd command to change the current directory. Handling paths,
 * updating env variables.
 */

int ft_cd(t_cmd *cmds, t_env *env)
{
    char    *path;
    char    current_dir[PATH_MAX];

    if (!cmds->args[1])
    {
        path = getenv("HOME");
        if (!path)
            return (ft_fdprintf(2, "cd: HOME not set\n"), FAIL);
    }
    else
        path = cmds->args[1];
    if (chdir(path) != 0)
    {
        ft_fdprintf(2, "cd: %s: %s\n", path, strerror(errno));
        return (FAIL);
    }
    if (getcwd(current_dir, sizeof(current_dir)) != NULL)
        update_env(env, "PWD", current_dir);
    else
    {
        ft_fdprintf(2, "cd: error getting current directory: %s\n", strerror(errno));
        return (FAIL);
    }
    return (SUCCESS);
}

void    update_env(t_env *tmp, char *str, char *current_dir)
{
    while (tmp->next)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			tmp->value = ft_strdup(current_dir);
			return ;
		}
		tmp = tmp->next;
	}
}
