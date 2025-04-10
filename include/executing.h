/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:15:35 by loribeir          #+#    #+#             */
/*   Updated: 2025/04/08 17:42:02 by lolq             ###   ########.fr       */
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
int     builtins_parent(t_shell *shell, t_cmd *cmds);
int     builtins_child(t_shell *shell, t_cmd *cmds);
int     ft_pwd(void);
int     ft_cd(t_cmd *cmds, t_env *env);
int     ft_env(t_shell *shell, t_cmd *cmds);
int     ft_echo(t_cmd *cmds);
int     ft_export(t_shell *shell, char **args);
void    ft_exit(t_shell *shell, t_cmd *cmds);
void    ft_unset(t_shell *shell, char **args);

/* BUILTINS: useful functions. */
int     verify_args_export(char *args);
void    update_export(t_env *tmp, char *key, char *value);
t_env   *add_var_back(t_env *env, char *key, char *value);
void    free_node_env(t_env *env);
t_env   *search_lst(t_env *env);
int     is_arg_nb(char *arg);
void    update_env(t_env *tmp, char *str, char *current_dir);
int		ft_strcharcmp(char *str, char comp);


/* EXECUTING: the main function calling all functions */
int    executing(t_shell *shell);

/* PATH: */
char    *search_env_path(t_env *env);
char    *search_in_path(char *cmd, char **path_split);
void    find_executable(t_cmd *cmds, t_env *env);

/* CHILD: */
int     create_child(t_shell *shell, t_cmd *cmds);
void    exec_child(t_cmd *cmds, t_shell *shell);
int     env_len(t_env *env);
void    wait_children(t_shell *shell);
char    **env_char(t_shell *shell);
void    handle_fork(t_shell *shell, t_cmd *cmd);

/* HANDLING FDS: */
void    handling_open(t_redir *redir, int flags, mode_t mode);
void    open_fds(t_cmd *cmds);
void    close_fds(t_cmd  *cmds);
void    ft_close_fds(t_redir *fd);

/* HANDLING PIPES: */
void    open_pipes(t_shell *shell, t_cmd *cmds);

/* DUP.C: */
int    get_fdin(t_cmd *cmd);
int    get_fdout(t_cmd *cmd);
void    ft_dup(t_cmd *cmd);

#endif