/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:02:15 by lolq              #+#    #+#             */
/*   Updated: 2025/03/19 10:33:03 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief echo have to write arguments to minishell output.
 * And echo -n will not add a newline.
 */

int   ft_echo(t_cmd *cmds)
{
    char   **args;
    int     no_nl;
    int     i;

    //(void)no_nl;
    no_nl = 0;
    i = 1;
    args = cmds->args;
    if (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        no_nl = 1;
        i++;
    }
    while (args[i])
    {
        if (args[i + 1] == NULL)
            ft_fdprintf(1, "%s", args[i]);
        else  
            ft_fdprintf(1, "%s ", args[i]);
        i++;
    }  
    if (no_nl == 0)
        ft_fdprintf(1, "\n");
    return (SUCCESS);
}
