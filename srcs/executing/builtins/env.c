/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:12:37 by loribeir          #+#    #+#             */
/*   Updated: 2025/04/24 13:45:38 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief: env should display all the variable of the environnement.
 */

 int   ft_env(t_shell *shell, t_cmd *cmds)
{
    t_env   *current;
    
    current = shell->env;
    if (cmds->args[1])
    {
        if (cmds->args[1])
        {
            ft_fdprintf(2, "env: '%s': No such file or directory\n", cmds->args[1]);
            shell->exit_status = 127;
            return (FAIL);
        }
    }
    shell->exit_status = 0;
    while (current)
    {
        if (current->value)
            ft_fdprintf(1, "%s=%s\n", current->key, current->value);
        /*else
            ft_fdprintf(1, "%s=n", current->key);*/
        current = current->next;
    }
   return (SUCCESS);
}
 