/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:42:03 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/30 11:38:30 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "minishell.h"

/*######	TOKEN 	######*/
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC,
	ENV_VAR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
	int				skip;
}	t_token;

# define SYNTAX_ERR_PIPE "minishell: syntax error near unexpected token `|'\n"

void print_redir_list(t_redir *redir_list, const char *type);
void print_cmd_list(t_cmd *cmd_list);
void print_env_list(t_env *env);
void	debug_here_doc(char *filepath, char *limiter);
void	debug_pre_parsing(char *str);
void afficher_tableau(char **tableau);
const char *token_type_to_string(t_token_type type);
void view_token_struct(const t_token *liste);

/* init.c */
t_cmd			*init_cmd(void);
t_pipe			*init_pipe(void);

/* parsing.c */
t_shell			*parsing(t_shell *shell, char *line, int argc, char **argv);

/* pre_parsing.c */
void			update_quotes_calc(char c, int *in_sq, int *in_dq);
int				add_space_size(const char *line, int i);
int				calculate_buffer_size(const char *line);
char			*pre_parsing(char *line);

/* pre_parsing_utils.c */
void			update_quotes(char c, int *in_sq, int *in_dq);
int				is_operator(char c);
void			handle_operator(char *new_line, char *line, int *i, int *j);

/* ft_split/ft_split_sh.c */
char			**ft_split_sh(const char *s, char c);
char			**ft_cpystr(char **tab, const char *s, char c, int nb);
int				ft_get_word_len(const char *s, int *i, char c);
void			ft_update_quotes(const char *s, int *i, int *sq, int *dq);

/* ft_split/ft_split_sh.c */
void			ft_freetab(char **tab, int n);
int				ft_countnbr(const char *str, char c);
void			ft_skip_word(const char *str, int *i, char c);
void			ft_skip_sep(const char *str, int *i, char c);

/* token.c */
t_token			*create_token(char *line_content, t_token *prev);
t_token			*tokenization(char **line, int i);
t_token_type	tokenization_set_type(char *word);

/* cmds.c */
t_cmd			*create_cmd(t_token *token, t_shell *shell);
int				process_token(t_shell *shell, t_token *token, t_cmd *current_cmd);
void			process_command(t_cmd *cmd_list, t_shell *shell);
void			guess_redir(t_shell *shell, t_cmd *cmd, t_token *token);
void			add_args(t_cmd *cmd, char *arg);

/* cmds_redir.c */
int				add_redir(t_redir **redir_list, t_token *token, \
							t_redir_type type, t_shell *shell);
void			append_redir(t_redir **redir_list, t_redir *new_redir);
int				setup_heredoc(t_redir *redir, t_token *token);
t_redir			*create_new_redir(t_token *token, t_redir_type type, t_shell *shell);

/* built_in.c */
bool			is_built_in(char **cmds);

/* pipe.c */
void			create_pipe(t_cmd *cmds);

/* env.c */
t_env			*add_env_node(t_env *node, char *env);
t_env			*copy_env(char **envp);

/* env_var.c */
void			execute_env_var(t_shell *shell, char **args);
char			*process_env_var(t_shell *shell, char *str);
void			handle_regular_char(char **res, char c);
void			handle_env_var(t_env *env, char **res, char *str, int *i);
int				handle_special_vars(t_shell *shell, \
						char **res, char *str, int *i);

/* env_var_utils.c */
void			handle_dollar_sign(t_shell *shell, char **result, \
						char *str, int *i);
void			append_str(char **result, const char *str);
int				is_var_char(char c);
char			*get_env_value(t_env *env, char *key);

/* env_var_case.c */
char			*ft_getexitcode(t_shell *shell);
void			remove_empty_args(char **args);

/* here_doc.c */
void			handle_heredoc_sigint(int sig);
int				open_here_doc_file(char *filepath, char *limit_with_nl, \
							int *fd);
void			setup_heredoc_signals(struct sigaction *old_int, \
							struct sigaction *old_quit);
char			*read_heredoc_lines(int fd, char *limit_with_nl);
char			*execute_here_doc(t_shell *shell, \
							char *filepath, char *limiter);
int				handle_here_doc(t_shell *shell, \
							t_redir *redir, int *id_here_doc);
int				execute_here_doc_cmds(t_cmd *cmds, t_shell *shell);

/* here_doc_.c */
void			clean_heredoc_files(t_cmd *cmds);

/* parentheses_utils.c */
int				process_parenthesis_char(char c, int *in_sq, \
							int *in_dq, int *count);
void			process_remove_parenthesis(const char *arg, \
							char *result, int *j, int *quotes);
int				handle_empty_result(char *result, const char *arg, int j);

/* parentheses.c */
int				check_parentheses(char **args);
char			*remove_parentheses(const char *arg);
void			interpret_parentheses(char **args);

/* quote.c */
int				quote(char **args);
char			*remove_quotes(const char *arg);
void			interpret_quotes(char **args);

/* error.c */
void			ft_perror(char *str, int exit_code);

/* free.c */
void			free_tokens(t_token *head);

#endif