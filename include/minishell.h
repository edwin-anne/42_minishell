/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:57:53 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/09 11:23:32 by Edwin ANNE       ###   ########.fr       */
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

# include "../libft/include/libft.h" 
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"

typedef enum e_redir_type
{
	NONE,
	FILE_REDIR,
	PIPE_REDIR,
	HERE_DOC,
	APPEND_REDIR
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type_in;    // Type de redirection en entrée
	char	        *file_in;   // Chemin fichier pour l'entrée (si type_in == FILE_REDIR)
	char			*limiter_here_doc;
	int		        fd_in;      // File descriptor pour l'entrée

	t_redir_type	type_out;   // Type de redirection en sortie
	char	        *file_out;  // Chemin fichier pour la sortie (si type_out == FILE_REDIR)
	int		        fd_out;     // File descriptor pour la sortie
}	t_redir;

typedef struct s_cmd
{
    char    **args;       // Arguments de la commande (argv)
    char    *path;        // Chemin vers l'exécutable
	struct s_redir *redir;
    bool     is_builtin;   // Indique si c'est une commande interne (1) ou externe (0)
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

/*######	FREE   	######*/
void	free_shell(t_shell *shell);
void	free_env(t_env *env);
void	free_cmds(t_cmd *cmd);
void	free_redir(t_redir *redir);

#endif

/*echo -n "test" | cat -e

cmd->path = /usr/bin/echo
cmd->args[0] = echo
cmd->args[1] = -n
cmd->args[2] = "test"
cmd->next->path = /usr/bin/cat
cmd->next->args[0] = cat
cmd->next->args[1] = -e*/
