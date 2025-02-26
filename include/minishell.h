/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:57:53 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/26 21:57:10 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <stdlib.h>

# include "../libft/include/libft.h" 
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"

typedef struct s_cmd
{
    char    **args;       // Arguments de la commande (argv)
    char    *path;        // Chemin vers l'exécutable
    int     fd_in;        // Descripteur de fichier pour l'entrée
    int     fd_out;       // Descripteur de fichier pour la sortie
    int     is_builtin;   // Indique si c'est une commande interne (1) ou externe (0)
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
    int     stdin_backup;  // Backup de stdin pour reset après redirections
    int     stdout_backup; // Backup de stdout pour reset après redirections
} t_shell;

/*######	UTILS   	######*/


#endif