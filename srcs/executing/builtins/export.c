/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:29:03 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/06 17:41:42 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

/**
 * @brief : export envp variables as child processes. 
 * The function should include a variable in the child process envp without
 * affecting other envp.
 * Without any argument, it will display all exported variables.
 */

void    export(t_shell *shell, char **args)
{
    int i;
    char    *eq_pos;

    i = 1;
    while (args[i])
    {
        if (verifyExport(args[i]) == SUCESS)
        {
            eq_pos = ft_strchr(args[i], '=');
            if (eq_pos)
            {
                /**eq_pos = '\0';
                shell->env->key = args[i];
                shell->env->value = eq_pos + 1;*/
                updateExport(shell, shell->env->key, shell->env->value);
            }
            i++;
        }
    }         
}
int  verifyExport(char *args)
{
    if (!ft_strchr(args, '='))
        return (FAIL);
    if (ft_isdigit(args[0]))
        return (ft_printf("bash: export: '%s': not a valid identifier\n", args[1]), FAIL);
    if (!ft_isalpha(args[0]) && args[0] != '_')
        return (ft_printf("bash: export: invalid option\n"), FAIL);
    return (SUCESS);
}
void    updateExport(t_shell *shell, char *key, char *value)
{
    /*while (shell->env)
    {
        if (ft_strcmp(shell->env->key, key) == 0)
        {
            //free(shell->env->value);
            shell->env->value = ft_strdup(value);
            return ;
        }
        shell->env = shell->env->next;
    }*/
    envAddBack(shell->env, key, value);
    /*new_env->key = ft_strdup(key);
    new_env->value = ft_strdup(value);
    new_env->next = shell->env;
    shell->env = new_env;
    shell->env->next = NULL;*/
}

