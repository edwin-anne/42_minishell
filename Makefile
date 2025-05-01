# NAME
NAME    = minishell

# DIRECTORIES
LIBFT   = ./libft/libft.a
INC     = include/
OBJS_DIR = obj/
SRC_DIR = srcs/

# COMPILER & FLAGS
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -I$(INC) -I./libft/include
LDFLAGS = -lreadline
RM      = rm -f

# SOURCES FILES
SRCS = \
	srcs/free_.c \
	srcs/free.c \
	srcs/main.c \
	srcs/executing/builtins/cd.c \
	srcs/executing/builtins/echo.c \
	srcs/executing/builtins/env.c \
	srcs/executing/builtins/exit.c \
	srcs/executing/builtins/export.c \
	srcs/executing/builtins/pwd.c \
	srcs/executing/builtins/unset.c \
	srcs/executing/exec/builtins.c \
	srcs/executing/exec/child.c \
	srcs/executing/exec/executing.c \
	srcs/executing/exec/ft_dup.c \
	srcs/executing/exec/handling_fork.c \
	srcs/executing/exec/handling_pipes.c \
	srcs/executing/exec/handling_redir.c \
	srcs/executing/exec/path.c \
	srcs/executing/utils/utils_builtins.c \
	srcs/executing/utils/utils_child.c \
	srcs/ft_fdprintf/ft_fdprintf_error.c \
	srcs/ft_fdprintf/ft_fdprintf_hexa.c \
	srcs/ft_fdprintf/ft_fdprintf_int.c \
	srcs/ft_fdprintf/ft_fdprintf.c \
	srcs/parsing/built_in.c \
	srcs/parsing/cmds_redir.c \
	srcs/parsing/cmds.c \
	srcs/parsing/env_var_case.c \
	srcs/parsing/env_var_utils.c \
	srcs/parsing/env_var.c \
	srcs/parsing/env.c \
	srcs/parsing/error.c \
	srcs/parsing/free.c \
	srcs/parsing/here_doc_.c \
	srcs/parsing/here_doc.c \
	srcs/parsing/init.c \
	srcs/parsing/parentheses_utils.c \
	srcs/parsing/parentheses.c \
	srcs/parsing/parsing.c \
	srcs/parsing/pipe.c \
	srcs/parsing/pre_parsing_utils.c \
	srcs/parsing/pre_parsing.c \
	srcs/parsing/quote.c \
	srcs/parsing/token.c \
	srcs/parsing/ft_split/ft_split_sh_utils.c \
	srcs/parsing/ft_split/ft_split_sh.c \
	srcs/signal/signal.c

OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

# RULES
all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

#COMPILE OBJ FROM SRCS
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJS_DIR)
	@make clean -C ./libft

fclean: clean 
	@$(RM) $(NAME)
	@make fclean -C ./libft

re: fclean all 

.PHONY : all clean fclean re