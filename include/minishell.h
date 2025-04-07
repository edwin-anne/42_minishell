/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolq <lolq@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:57:53 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/07 09:17:40 by lolq             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/signal.h>

# include "../libft/include/libft.h" 
# include "ft_fdprintf.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"

typedef enum e_redir_type
{
    NO_REDIR,
    INPUT_REDIR,   // "<"
    HEREDOC,       // "<<"
    OUTPUT_REDIR,  // ">"
    APPEND_REDIR   // ">>"
}   t_redir_type;

typedef struct s_redir
{
    t_redir_type    type;       // Type de redirection
    char            *file;      // Nom du fichier (si applicable)
    char            *limiter;   // Limiteur pour heredoc (si applicable)
    int             fd;         // File descriptor associé
    struct s_redir  *next;      // Pointeur vers la prochaine redirection
}   t_redir;

typedef struct s_cmd
{
    char         **args;       // Arguments de la commande (argv)
    char         *path;        // Chemin vers l'exécutable
    pid_t        pid;          // pid d'une cmd
	t_redir      *redir_in;   // Liste chaînée des redirections d'entrée
    t_redir      *redir_out;
    bool         is_builtin;   // Indique si c'est une commande interne (1) ou externe (0)
    int          pipe_fd[2]; // 
    struct s_env *env;
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

/*######	SIGNAUX   	######*/
void	init_signals(void);

/*######	FREE   	######*/
void	free_shell(t_shell *shell);
void	free_env(t_env *env);
void	free_cmds(t_cmd *cmd);
void	free_redir(t_redir *redir);
void	free_char_array(char **array);

#endif
