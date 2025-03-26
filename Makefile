
# Library Name
NAME        = minishell

# Libraries
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Complier and Flags
CC          = cc
CFLAGS      = -g -Wall -Wextra -Werror
RM          = rm -f

# Colors used for terminal output.
GREEN = \033[0;32m
BLUE = \033[0;34m
ORANGE = \033[38;5;214m
RED = \033[0;31m
YELLOW = \033[0;33m
WHITE = \033[0;37m
RESET = \033[0m

# Readline
RL_PATH = $(shell brew --prefix readline)
RL_FLAGS = -I$(RL_PATH)/include -L$(RL_PATH)/lib -lreadline

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = inc

# Source files
	
SRC_FILES   = main.c \
			Parser/main_utils.c \
			Parser/main_utils_2.c \
			Parser/inits.c \
			Parser/tokenizer.c \
			Parser/tokenizer_utils.c \
			Parser/tokenizer_utils_2.c \
			Parser/tokenizer_utils_3.c \
			Parser/tokenizer_utils_4.c \
			Parser/syntax.c \
			Parser/syntax_utils.c \
			Parser/syntax_utils_2.c \
			Parser/parser.c \
			Parser/parser_utils.c \
			Parser/parser_utils_2.c \
			Parser/free.c \
			Parser/free_2.c \
			Signals/signals.c \
			Signals/signals_utils.c \
			Executor/builtins/export.c \
			Executor/builtins/export_utils.c \
			Executor/executor.c \
			Executor/executor_helper_ft.c \
			Executor/print_ft.c \
			Executor/init_structs.c \
			Executor/builtins.c \
			Executor/redirections.c \
			Executor/pipe.c \
			Executor/builtins/exit.c



SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INC         = -I$(INC_DIR) -I$(LIBFT_DIR)/inc

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $< ...$(RESET)"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Main target
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(RL_FLAGS)
	@echo "$(GREEN)** $(NAME) Compiled successfully! **"

# Libft Dependency (Build)
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Cleanup rules
# TEST REMOVE ME TODO
clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(YELLOW)** $(NAME) removed! **$(RESET)"

re: fclean all

.PHONY: all clean fclean re
