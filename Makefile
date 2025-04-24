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

# SOURCES FILES (recherche automatique)
SRCS    = $(shell find $(SRC_DIR) -type f -name "*.c")
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