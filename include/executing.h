/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:15:35 by loribeir          #+#    #+#             */
/*   Updated: 2025/03/06 17:11:57 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
#define EXECUTING_H

#include "minishell.h"

/* USEFUL DEFINE */
#define SUCESS 0
#define FAIL 1

/* BUILTINS: */
void     export(t_shell *shell, char **args);
int      verifyExport(char *args);
void     updateExport(t_shell *shell, char *key, char *value);
void    envAddBack(t_env *env, char *key, char *value);
t_env    *envLast(t_env *env);

//static int      errorExport(const char *message);

#endif