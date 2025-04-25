/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:41:45 by lolq              #+#    #+#             */
/*   Updated: 2025/04/25 09:37:44 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief: cd command change the current directory. Handling paths,
 * updating env variables.
 */

int ft_cd(t_shell *shell, t_cmd *cmds, t_env *env)
{
    char    *path;
    char    current_dir[PATH_MAX];

    path = ft_cd_path(env, cmds);
    if (!path)
        return (cd_error(shell, "HOME not set", NULL));
    if (chdir(path) != 0)
        return (cd_error(shell, strerror(errno), path));
    if (!getcwd(current_dir, sizeof(current_dir)))
        return (cd_error(shell, strerror(errno), "error getting current directory"));
    if (cmds->args[2])
        return (cd_error(shell, "too many arguments", "cd"));
    update_env(env, "PWD", current_dir);
    shell->exit_status = 0;
    return (SUCCESS);
}

char    *ft_cd_path(t_env *env, t_cmd *cmds)
{
    if (!cmds->args[1])
        return (get_env(env, "HOME"));
    return (cmds->args[1]);
}

int cd_error(t_shell *shell, char *msg, char *arg)
{
    shell->exit_status = 1;
    if (arg)
        ft_fdprintf(2, "minishell: %s: %s\n", arg, msg);
    else
        ft_fdprintf(2, "minishell: %s\n", msg);
    return (FAIL);
        
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

char    *get_env(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_constcmp(env->key, key) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}
