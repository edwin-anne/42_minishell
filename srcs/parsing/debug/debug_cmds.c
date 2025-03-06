/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:21:22 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/02 12:35:52 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"

void print_redir(t_redir *redir)
{
    if (!redir)
    {
        printf("  Redirections: None\n");
        return;
    }

    printf("  Redirections:\n");
    
    // Affichage de l'entrée
    if (redir->type_in == FILE_REDIR)
        printf("    Input: File - %s (fd: %d) (file: %s)\n", redir->file_in, redir->fd_in, redir->file_in);
    else if (redir->type_in == PIPE_REDIR)
        printf("    Input: Pipe (fd: %d)\n", redir->fd_in);
    else if (redir->type_in == HERE_DOC)
        printf("    Input: Here Document (fd: %d) (file: %s)\n", redir->fd_in, redir->file_in);
    else
        printf("    Input: None\n");

    // Affichage de la sortie
    if (redir->type_out == FILE_REDIR)
        printf("    Output: File - %s (fd: %d)\n", redir->file_out, redir->fd_out);
    else if (redir->type_out == PIPE_REDIR)
        printf("    Output: Pipe (fd: %d)\n", redir->fd_out);
    else
        printf("    Output: None\n");
}

void print_cmd_list(t_cmd *cmd_list)
{
    int cmd_index = 1;
    
    printf("\n========= Liste des commandes =========\n");
    while (cmd_list)
    {
        printf("\nCommande %d:\n", cmd_index++);
        printf("  Path: %s\n", cmd_list->path ? cmd_list->path : "(NULL)");

        printf("  Arguments: ");
        if (cmd_list->args)
        {
            for (int i = 0; cmd_list->args[i]; i++)
                printf("\"%s\" ", cmd_list->args[i]);
        }
        else
        {
            printf("(NULL)");
        }
        printf("\n");

        printf("  Builtin: %s\n", cmd_list->is_builtin ? "Yes" : "No");

        print_redir(cmd_list->redir);
        
        printf("--------------------------------------\n");

        cmd_list = cmd_list->next;
    }
    printf("=======================================\n");
}
