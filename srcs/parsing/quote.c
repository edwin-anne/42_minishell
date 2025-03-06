/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:12:01 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/05 14:23:23 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <stdio.h>

void quote(char **args) {
    int i = 0;
    int single_quote_open = 0;
    int double_quote_open = 0;

    while (args[i]) {
        char *arg = args[i];
        while (*arg) {
            if (*arg == '\'' && double_quote_open == 0) {
                single_quote_open = !single_quote_open;
            } else if (*arg == '"' && single_quote_open == 0) {
                double_quote_open = !double_quote_open;
            }
            arg++;
        }
        i++;
    }

    if (single_quote_open) {
        printf("minishell: syntax error near unexpected token `'`\n");
    }
    if (double_quote_open) {
        printf("minishell: syntax error near unexpected token `\"`\n");
    }
}
