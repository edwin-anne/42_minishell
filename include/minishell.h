/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loribeir <loribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:57:53 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/26 21:05:06 by loribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>

# include "../libft/include/libft.h" 
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"

typedef struct s_cmd
{
    char    **args;       // Arguments de la commande (argv)
    char    *path;        // Chemin vers l'exécutable
    int     fd_in;        // Descripteur de fichier pour l'entrée
    int     fd_out;       // Descripteur de fichier pour la sortie
    bool     is_builtin;   // Indique si c'est une commande interne (1) ou externe (0)
    struct s_cmd *next;   // Commande suivante (utile pour les pipes)
} t_cmd;

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
} t_env;

typedef struct s_shell
{
    t_env   *env;        // Liste chaînée des variables d'environnement
    t_cmd   *cmds;       // Liste des commandes à exécuter
    int     exit_status; // Code de retour du dernier processus
} t_shell;

/*######	UTILS   	######*/


#endif

/*echo -n "test" | cat -e

cmd->path = /usr/bin/echo
cmd->args[0] = echo
cmd->args[1] = -n
cmd->args[2] = "test"
cmd->next->path = /usr/bin/cat
cmd->next->args[0] = cat
cmd->next->args[1] = -e*/
