/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:15:35 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/13 18:19:16 by lolq             ###   ########.fr       */
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
void    free_node_env(t_env *env);
t_env   *search_lst(t_env *env);
//
int   ft_env(t_shell *shell, char **args);
//
int   ft_echo(t_shell *shell);
//
int    ft_pwd(void);

#endif