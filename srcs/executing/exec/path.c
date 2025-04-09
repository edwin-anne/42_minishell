/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:49:26 by lolq              #+#    #+#             */
/*   Updated: 2025/04/09 14:12:04 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief: find the full path of executable cmd using the system's PATH. 
 * - searches for the PATH env variable in the linked list.
 * - use the PATH to locate the exec file.
 * - add the path to the structure.
 */

char    *search_env_path(t_env *env)
{
    t_env   *tmp;

    tmp = env;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->key, "PATH" ) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void    find_executable(t_cmd *cmds, t_env *env)
{
    char    **path_split;
    char    *path_value;

    if (cmds->is_builtin == true)
        return ;
    path_value = search_env_path(env);
    if (!path_value)
        return ;
    path_split = ft_split(path_value, ':');
    if (!path_split)
        return ;
    if (access(cmds->args[0], X_OK) == 0)
    {
        cmds->path = cmds->args[0];
        free_char_array(path_split);
        return ;
    }
    cmds->path = search_in_path(cmds->args[0], path_split);
    free_char_array(path_split);
}

char    *search_in_path(char *cmd, char **path_split)
{
    char    *tmp;
    char    *full_path;
    int     i;

    i = 0;
    while (path_split[i])
    {
        tmp = ft_strjoin(path_split[i], "/");
        if (!tmp)
            return (NULL);
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        i++; 
    }
    return (NULL);
}
