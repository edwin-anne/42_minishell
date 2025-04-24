/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:45:19 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/24 16:09:04 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_parentheses(char **args)
{
    int     i;
    int     count;
    char    *arg;

    i = 0;
    count = 0;
    if (!args)
        return (0);
    while (args[i])
    {
        arg = args[i];
        while (*arg)
        {
            if (*arg == '(')
                count++;
            else if (*arg == ')')
            {
                count--;
                if (count < 0)
                    return (0);
            }
            arg++;
        }
        i++;
    }
    return (count == 0);
}

char    *remove_parentheses(const char *arg)
{
    int     i;
    int     j;
    char    *result;

    if (!arg)
        return (NULL);
    result = malloc(ft_strlen(arg) + 1);
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (arg[i])
    {
        if (arg[i] != '(' && arg[i] != ')')
            result[j++] = arg[i];
        i++;
    }
    result[j] = '\0';
    if (j == 0 && arg[0] != '\0')
    {
        free(result);
        return (ft_strdup(arg));
    }
    return (result);
}

void    interpret_parentheses(char **args)
{
    int     i;
    char    *processed;

    i = 0;
    if (!args)
        return ;
    if (!check_parentheses(args))
    {
        ft_fdprintf(2, "minishell: syntax error near unexpected token `('\n");
        return ;
    }
    while (args[i])
    {
        processed = remove_parentheses(args[i]);
        if (processed)
        {
            free(args[i]);
            args[i] = processed;
        }
        i++;
    }
}

