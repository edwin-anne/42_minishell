/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:15:35 by loribeir          #+#    #+#             */
/*   Updated: 2025/04/26 14:56:34 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
#define EXECUTING_H

#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>

/* USEFUL DEFINE */
#define SUCCESS 0
#define FAIL 1
#define PATH_MAX 4096

/* BUILTINS: all builtins functions */
int     builtins_parent(t_shell *shell, t_cmd *cmds);
int     builtins_child(t_shell *shell, t_cmd *cmds);
int    ft_pwd(t_shell *shell);
int     ft_cd(t_shell *shell, t_cmd *cmds, t_env *env);
int     ft_env(t_shell *shell, t_cmd *cmds);
int     ft_echo(t_cmd *cmds);
int     ft_export(t_shell *shell, t_cmd *cmds);
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
char    *get_env(t_env *env, const char *key);
char    *ft_cd_path(t_env *env, t_cmd *cmds);
int		ft_strcharcmp(char *str, char comp);
int		ft_constcmp(char *s1, const char *s2);
int     cd_error(t_shell *shell, char *msg, char *arg);


/* EXECUTING: the main function calling all functions */
int    executing(t_shell *shell);

/* PATH: */
char    *search_env_path(t_env *env);
char    *search_in_path(char *cmd, char **path_split);
void    find_executable(t_cmd *cmds, t_env *env);
int     exec_error(t_shell *shell, t_cmd *cmds);

/* CHILD: */
int     create_child(t_shell *shell, t_cmd *cmds);
void    exec_child(t_cmd *cmds, t_shell *shell);
int     env_len(t_env *env);
void    wait_children(t_shell *shell);
char    **env_char(t_shell *shell);

/*HANDLING FORK: */
void    handle_fork(t_shell *shell, t_cmd *cmd);
int     handle_redirout(t_shell *shell, t_cmd *cmd);
int     handle_redirin(t_shell *shell, t_cmd *cmd);

/* HANDLING PIPES: */
void    open_pipes(t_shell *shell, t_cmd *cmds);
void    close_pipes(t_cmd *cmd);

/* FT_DUP: */
void    ft_dup(t_cmd *cmd);
int     get_fdout(t_cmd *cmd);
int     get_fdin(t_cmd *cmd);

/* HANDLING REDIR: */
int    check_redir_in(t_redir *redir_in);
int    check_redir_out(t_redir *redir_out);
void   ft_dup_redir(t_redir *in, t_redir *out);
void   redir_error(char *file);

#endif