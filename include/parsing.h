/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:42:03 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/29 13:31:41 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

/*######	TOKEN 	######*/
typedef enum e_token_type {
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HERE_DOC,
    ENV_VAR
} t_token_type;

typedef struct s_token {
    t_token_type type;
    char *value;
    struct s_token *next;
    struct s_token *prev;
    int skip;
} t_token;

# define SYNTAX_ERR_PIPE "minishell: syntax error near unexpected token `|'\n"

/*######	INIT 	######*/
t_cmd			*init_cmd(void);
t_pipe          *init_pipe(void);

/*######	PARSING 	######*/
t_shell			*parsing(t_shell *shell, char *line, int argc, char **argv);

/*######	PRE PARSING 	######*/
char			*pre_parsing(char *line);
void	        update_quotes(char c, int *in_sq, int *in_dq);
int	            is_operator(char c);
void	        handle_operator(char *new_line, char *line, int *i, int *j);

/*######	CMDS 	######*/
void			add_args(t_cmd *cmd, char *arg);
int             add_redir(t_redir **redir_list, t_token *token, t_redir_type type);
void            guess_redir(t_cmd *cmd, t_token *token);
void	        process_command(t_cmd *cmd_list, t_shell *shell);
int	            process_token(t_token *token, t_cmd *current_cmd);
t_cmd           *create_cmd(t_token *token, t_shell *shell);

/*######	TOKEN 	######*/
t_token			*tokenization(char **line, int i);
t_token_type	tokenization_set_type(char *word);

/*######	ENVIRONNEMENT 	######*/
t_env			*copy_env(char **envp);
t_env			*add_env_node(t_env *node, char *env);

/*######	QUOTE 	######*/
int             quote(char **args);
void            interpret_quotes(char **args);
char	        *remove_quotes(const char *arg);

/*######	BUILT_IN 	######*/
bool			is_built_in(char **cmds);

/*######	HERE_DOC 	######*/
char			*execute_here_doc(char *filepath, char *limiter);
int             execute_here_doc_cmds(t_cmd *cmds);

/*######	ENV_VAR 	######*/
void	        execute_env_var(t_shell *shell, char **args);
void            name_env_var(char c, char **result);
void            append_str(char **result, const char *str);
void	        handle_dollar_sign(t_shell *shell, char **result, char *str, int *i);
void	        handle_env_var(t_env *env, char **res, char *str, int *i);
int	            handle_special_vars(t_shell *shell, char **res, char *str, int *i);
void	        handle_regular_char(char **res, char c);

/*######	ENV_VAR_CASE 	######*/
char            *ft_getpid();
char            *ft_getexitcode(t_shell *shell);

/*######	ENV_VAR_UTILS 	######*/
char	        *get_env_value(t_env *env, char *key);
int             is_var_char(char c);
void            append_str(char **result, const char *str);
int             update_quote_state(char c, int *in_sq, int *in_dq);

/*######	PIPE 	######*/
void            create_pipe(t_cmd *cmds);

/*######	UTILS 	######*/
/*######	FT_SPLIT_MULTI  	######*/
int             ft_countnbr(const char *str, char c);
void	        ft_freetab(char **tab, int n);
void	        ft_skip_sep(const char *str, int *i, char c);
char	        **ft_split_sh(char const *s, char c);

/*######	FREE 	######*/
void            free_tokens(t_token *head);

/*######	ERROR 	######*/
void			ft_perror(char *str, int exit_code);

/*######	DEBUG 	######*/
/*######	TOKEN 	######*/
void			afficher_tableau(char **tableau);
void			view_token_struct(const t_token *liste);

/*######	DEBUG 	######*/
/*######	HERE_DOC 	######*/
void			debug_here_doc(char *filepath, char *limiter);

/*######	DEBUG 	######*/
/*######	CMDS 	######*/
void			print_cmd_list(t_cmd *cmd_list);

/*######	DEBUG 	######*/
/*######	ENV 	######*/
void			print_env_list(t_env *env);

/*######	DEBUG 	######*/
/*######	PRE_PARSING 	######*/
void			debug_pre_parsing(char *str);

/*######	PARENTHESES HANDLING 	######*/
int				check_parentheses(char **args);
char			*remove_parentheses(const char *arg);
void			interpret_parentheses(char **args);
int             process_char(char c, int *count, int *in_sq, int *in_dq);
void            update_quote_state_2(char c, int *in_sq, int *in_dq);
int             is_parenthesis_to_skip(char c, int in_sq, int in_dq);

#endif