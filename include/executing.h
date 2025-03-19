/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:15:35 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/19 16:50:43 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
#define EXECUTING_H

#include "minishell.h"

/* USEFUL DEFINE */
#define SUCCESS 0
#define FAIL 1
#define PATH_MAX 4096

/* BUILTINS: all builtins functions */
int     ft_pwd(void);
int     ft_cd(t_cmd *cmds, t_env *env);
int     ft_env(t_shell *shell, t_cmd *cmds);
int     ft_echo(t_cmd *cmds);
int     ft_export(t_shell *shell, char **args);
void    ft_exit(t_shell *shell, t_cmd *cmds);
void    ft_unset(t_shell *shell, char **args);
//
/* BUILTINS: useful functions. */
int     verify_args_export(char *args);
void    update_export(t_env *tmp, char *key, char *value);
t_env   *add_var_back(t_env *env, char *key, char *value);
//
void    free_node_env(t_env *env);
t_env   *search_lst(t_env *env);
int     is_arg_nb(char *arg);
void    update_env(t_env *tmp, char *str, char *current_dir);
//
/* EXECUTING: calling all main functions */
int    builtins_executing(t_shell *shell, t_cmd *cmds);

/* PATH: */
char    *search_env_path(t_env *env);
char    *search_in_path(char *cmd, char **path_split);
void    find_executable(t_cmd *cmds, t_env *env);

// 

#endif