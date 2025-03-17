/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:08:04 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/16 10:31:26 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *init_cmd(void)
{
    t_cmd *cmd;

    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);

    cmd->args = NULL;
    cmd->path = NULL;
    cmd->is_builtin = false;
    cmd->next = NULL;

    cmd->redir_in = NULL;
    cmd->redir_out = NULL;

    return (cmd);
}
