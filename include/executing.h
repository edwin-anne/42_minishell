/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:15:35 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/09 15:25:36 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
#define EXECUTING_H

#include "minishell.h"

/* USEFUL DEFINE */
#define SUCCESS 0
#define FAIL 1

/* BUILTINS: */
void    ft_export(t_shell *shell, char **args);
int     verify_args_export(char *args);
void    update_export(t_env *tmp, char *key, char *value);
t_env   *add_var_back(t_env *env, char *key, char *value);
//
void    ft_unset(t_shell *shell, char **args);
void    unset_value(t_shell *shell, t_env *prev, t_env *tmp, char *arg);
t_env   *remove_var(t_env *env, t_env *prev);
void    free_node_env(t_env *env);
t_env   *search_lst(t_env *env);


#endif