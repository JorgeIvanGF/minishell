#include "minishell.h"
#include "execution.h"

// minishell - cmd not found - 1
void error_cmd_not_found(char *cmd_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(": command not found", 2);
}

// env - no such file or directory - 1
void error_env_no_file_directory(char *arg2)
{
	write(2, "env: ", 5);
	write(2, arg2, ft_strlen(arg2));
	write(2, ": No such file or directory\n", 28);
}

// minishell - heredoc fail - 2
void error_heredoc()
{
	write(2, "minishell: ", 11);
	write(2, "heredoc fail\n", 13);
}

// minishell - no such file or directory - 3
void error_no_file_directory(char *rdir_name)
{
	write(2, "minishell: ", 11);
	write(2, rdir_name, ft_strlen(rdir_name));
	write(2, ": No such file or directory\n", 28); 
}
