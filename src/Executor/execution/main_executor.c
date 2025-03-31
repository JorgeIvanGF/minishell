#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

// main execution
// for testing purposes: print_list_commands(minishell->list_cmd);
int	ft_execution(t_minishell *minishell)
{
	save_io_fds(minishell);
	iterate_and_execute_cmd_list(minishell);
	restore_io(minishell);
	return (minishell->exit_code);
}