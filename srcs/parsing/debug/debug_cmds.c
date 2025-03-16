/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:21:22 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/16 10:16:58 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"

void print_redir_list(t_redir *redir_list, const char *type)
{
    if (!redir_list)
    {
        printf("    %s: None\n", type);
        return;
    }

    printf("    %s:\n", type);
    while (redir_list)
    {
        if (redir_list->type == INPUT_REDIR)
            printf("      - Input: File - %s (fd: %d)\n", redir_list->file, redir_list->fd);
        else if (redir_list->type == HEREDOC)
            printf("      - Input: Here Document (fd: %d) (limiter: %s)\n", redir_list->fd, redir_list->limiter);
        else if (redir_list->type == OUTPUT_REDIR)
            printf("      - Output: File - %s (fd: %d)\n", redir_list->file, redir_list->fd);
        else if (redir_list->type == APPEND_REDIR)
            printf("      - Output: Append - %s (fd: %d)\n", redir_list->file, redir_list->fd);
        else
            printf("      - Unknown redirection type\n");

        redir_list = redir_list->next;
    }
}

void print_cmd_list(t_cmd *cmd_list)
{
    int cmd_index = 1;

    printf("\n========= Liste des commandes =========\n");
    while (cmd_list)
    {
        printf("\nCommande %d:\n", cmd_index++);
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

        // Affichage des redirections multiples
        print_redir_list(cmd_list->redir_in, "Redirections d'entrée");
        print_redir_list(cmd_list->redir_out, "Redirections de sortie");

        printf("--------------------------------------\n");

        cmd_list = cmd_list->next;
    }
    printf("=======================================\n");
}
