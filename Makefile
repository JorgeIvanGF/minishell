# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 17:55:02 by jorgutie          #+#    #+#              #
#    Updated: 2025/02/23 03:53:15 by pdrettas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library Name
NAME        = minishell

# Libraries
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Complier and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
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
SRC_FILES   = main.c Executor/executor.c Executor/executor_helper_ft.c
			
			

SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INC         = -I$(INC_DIR) -I$(LIBFT_DIR)/inc

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Main target
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(RL_FLAGS)
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
