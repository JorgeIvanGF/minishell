# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 16:25:40 by jorgutie          #+#    #+#              #
#    Updated: 2025/03/10 20:49:50 by pdrettas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Path to header files
INC = -I./inc

# Directories
OBJDIR = obj
SRCDIR = src

# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror $(INC)

# Source files
SRCS = ft_atoi.c \
	   ft_atoi_long.c \
	   ft_bzero.c \
	   ft_calloc.c \
	   ft_free_2d.c \
	   ft_free.c \
	   ft_isalnum.c \
	   ft_isalpha.c \
	   ft_isascii.c \
	   ft_isdigit.c \
	   ft_isprint.c \
	   ft_itoa.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_memset.c \
	   ft_putchar_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_putstr_fd.c \
	   ft_split.c \
	   ft_strchr.c \
	   ft_strcmp.c \
	   ft_strdup.c \
	   ft_striteri.c \
	   ft_strjoin.c \
	   ft_strlcat.c \
	   ft_strlcpy.c \
	   ft_strlen.c \
	   ft_strmapi.c \
	   ft_strncmp.c \
	   ft_strnstr.c \
	   ft_strrchr.c \
	   ft_strtrim.c \
	   ft_substr.c \
	   ft_swap.c \
	   ft_tolower.c \
	   ft_toupper.c \
	   ft_uitoa.c \
	   ft_printf.c \
	   ft_printf_functions_1.c \
	   get_next_line_utils.c \
	   get_next_line.c

# Bonus Part
BONUS_SRCS = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c	\
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c	   


# Object files
OBJS = $(SRCS:.c=.o)

# Object files for the bonus functions
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# .obj to Folders
SRC = $(addprefix $(SRCDIR)/, $(SRCS))
OBJ = $(addprefix $(OBJDIR)/, $(OBJS))
BONUS_OBJ = $(addprefix $(OBJDIR)/, $(BONUS_OBJS))

# Name of the library
NAME = libft.a

# Rules
all: $(NAME)

# OJO-> averiguar
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

# Rule to compile the bonus functions
bonus: $(BONUS_OBJ)
	@ar rcs $(NAME) $(BONUS_OBJ)

# Pattern rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	@rm -f $(OBJ) $(BONUS_OBJ)
	@if [ -d "$(OBJDIR)" ]; then \
		rmdir $(OBJDIR); \
	fi

# Clean up the library and object files
fclean: clean
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re