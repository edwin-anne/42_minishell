/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:29:03 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/08 15:04:16 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

/**
 * @brief For minishell, export should behave like this: 
 * when we bump into valid arg(s), the variable should be added to the envp.
 * it should work fine with one or multiple arguments.
 */

void    ft_export(t_shell *shell, char **args)
{
    int     i;
    t_env   *tmp;
    char    **env_val;

    tmp = shell->env;
    i = 0;
    while (args[i])
    {
        env_val = ft_split(shell->cmds->args[i], '=');
        if (verify_args_export(args[i]) == SUCCESS)
            update_export(tmp, env_val[0], env_val[1]);
        i++;
    }
}

int verify_args_export(char *args)
{
    if (!ft_strchr(args, '='))
        return (FAIL);
    else if (ft_isdigit(args[0]))
        return (ft_printf("bash: export: '%s': not a valid identifier\n", args), FAIL);
    else if (ft_isalpha(args && args[0] != '_'))
        return (ft_printf("bash: export: invalid option\n"), FAIL);
    return (SUCCESS);
}

void    update_export(t_env *tmp, char *key, char *value)
{
    while (tmp->next)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            tmp->value= ft_strdup(value);
            printf("traasd\n");
            return ;
        }
        tmp = tmp->next;
    }
    add_var_back(tmp, key, value);
}


