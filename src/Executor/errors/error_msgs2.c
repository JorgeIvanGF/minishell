#include "minishell.h"
#include "execution.h"

// exit - minishell exit - too many arguments
void error_arguments_exceeded(t_minishell *minishell)
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	minishell->exit_code = 1;
	exit_code_num = minishell->exit_code ; //TODO: delete
}

// exit - minishell exit - numeric argument required
void error_no_numeric_argument(char *cmd_name, t_minishell *minishell)
{
	// ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(": numeric argument required", 2);
	minishell->exit_code = 255;
	 exit_code_num = minishell->exit_code ; //TODO: delete
	exit_shell(minishell);
}
