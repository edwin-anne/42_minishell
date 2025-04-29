/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:57:53 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 15:07:52 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/signal.h>

# include "../libft/include/libft.h" 
# include "ft_fdprintf.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"

typedef enum e_redir_type
{
	NO_REDIR,
	INPUT_REDIR,
	HEREDOC,
	OUTPUT_REDIR,
	APPEND_REDIR
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	char			*limiter;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipe
{
	int	pipe[2];
}	t_pipe;

typedef struct s_cmd
{
	char			**args;
	char			*path;
	pid_t			pid;
	int				has_child;
	t_redir			*redir_in;
	t_redir			*redir_out;
	bool			is_builtin;
	t_pipe			*pipe;
	int				*pipe_prev;
	struct s_env	*env;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmds;
	int		exit_status;
}	t_shell;

/*######	SIGNAUX   	######*/
void	init_signals(t_shell *shell);

/*######	FREE   	######*/
void	free_shell(t_shell *shell);
void	free_env(t_env *env);
void	free_cmds(t_cmd *cmd);
void	free_cmds_next(t_cmd *cmd);
void	free_redir(t_redir *redir);
void	free_char_array(char **array);
void	free_args(t_cmd *cmd);

#endif
