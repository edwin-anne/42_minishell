/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:02:15 by lolq              #+#    #+#             */
/*   Updated: 2025/03/11 16:54:43 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

/**
 * @brief Echo have to write arguments to minishell output.
 * And echo -n will not add a newline.
 */

 int   ft_echo(t_shell *shell)
 {
    char   **args;
    int     no_nl;
    int     i;
    
    (void)no_nl;
    no_nl = 0;
    i = 1;
    args = shell->cmds->args;
    if (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        no_nl = 1;
        i++;
    }
    while (args[i])
    {
        ft_printf("%s", args[i]);
        i++;
    }  
    if (no_nl == 0)
        ft_printf("\n");
    return (SUCCESS);
 }

 