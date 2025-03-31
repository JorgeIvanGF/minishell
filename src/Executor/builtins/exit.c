#include "execution.h"
#include "minishell.h"
#include "parsing.h"

int		syntax_check_exit(t_cmd *cmd, t_minishell *minishell);

// Executes exit with formula to calculate exit code
// If above 255, exit code needs to be "reset" through formula
int	execute_exit(t_cmd *cmd, t_minishell *minishell)
{
	if (syntax_check_exit(cmd, minishell) == 0)
		return (0);
	printf("exit\n");
	minishell->exit_code = ft_atoi(cmd->cmd_arr[1]) % 256;
	exit_shell(minishell);
	return (1);
}

// Parses exit by checking four cases
int	syntax_check_exit(t_cmd *cmd, t_minishell *minishell)
{
	check_null(cmd, minishell);
	check_empty(cmd, minishell);
	check_non_numeric(cmd, minishell);
	return (check_too_many_arguments(cmd, minishell));
}

