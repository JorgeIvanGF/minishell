#ifndef MINISHELL_H
# define MINISHELL_H

// Included Libraries_______________________________
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/inc/libft.h"
# include <termios.h>

//Colors used for terminal output____________________
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define ORANGE "\033[38;5;214m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"
# define B_RED "\033[1;31m"// Bright Red
# define MAG "\033[0;35m"// Magenta
# define CYAN "\x1b[36m" //Cyan

// Text attributes 
# define BOLD      "\x1b[1m" 
# define UNDERLINE "\x1b[4m"

// Enum Redirections_________________________________
typedef enum e_redirection_type
{
	RD_IN,
	RD_OUT,
	RD_APND,
	RD_HDOC
}	t_rdir_type;

// Redirection Struct________________________________
typedef struct s_redirection
{
	t_rdir_type				type;
	char					*name;
	struct s_redirection	*next;
}	t_rdir;

// Struct List Redirections__________________________
typedef struct s_list_rdirs
{
	int		size;
	t_rdir	*head;
	t_rdir	*tail;
}	t_lst_rdir;

// Command Struct____________________________________
typedef struct s_command
{
	char				**cmd_arr;
	t_lst_rdir			*list_rdir;
	struct s_command	*next;
}	t_cmd;

// List of Commands Struct__________________________
typedef struct s_list_commands
{
	int		size;
	t_cmd	*head;
	t_cmd	*tail;
}	t_lst_cmd;

// General Struct of minishell_______________________
typedef struct s_minishell
{
	char		**env;
	t_lst_cmd	*list_cmd;
	int			exit_code;
	int			og_stdin_fd;
	int			og_stdout_fd;
}	t_minishell;

// Execution________________________________________
int	ft_execution(t_minishell *minishell);

#endif
