/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:32:38 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/27 20:50:17 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void afficher_tableau(char **tableau)
{
    int i = 0;
    while (tableau[i] != NULL)
	{
        printf("%s -> ", tableau[i]);
        i++;
    }
}

const char *token_type_to_string(t_token_type type) {
    switch (type) {
        case WORD: return "WORD";
        case PIPE: return "PIPE";
        case REDIR_IN: return "REDIR_IN";
        case REDIR_OUT: return "REDIR_OUT";
        case APPEND: return "APPEND";
        case HEREDOC: return "HEREDOC";
        case ENV_VAR: return "ENV_VAR";
        default: return "UNKNOWN";
    }
}

void view_token_struct(const t_token *liste)
{
    const t_token *current = liste;
    printf("\n========= Liste des tokens =========\n\n");
    while (current != NULL) {
        printf("Type: %-10s | Valeur: %s\n", token_type_to_string(current->type), current->value);
        current = current->next;
    }
}