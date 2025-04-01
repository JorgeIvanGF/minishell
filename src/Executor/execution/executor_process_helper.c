#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

void	execution(t_cmd *cmd, t_minishell *minishell)
{
	char	*path;
	char	**path_cmds;
	char	*found_path;

	if (cmd == NULL || cmd->cmd_arr == NULL || cmd->cmd_arr[0] == NULL)
	{
		minishell->exit_code = 0;
		exit_shell(minishell);
	}
	path = get_path(minishell->env);
	path_cmds = get_paths_cmds(path);
	found_path = find_path(path_cmds, cmd->cmd_arr[0]);
	if (execute(found_path, cmd, minishell->env) == -1)
	{
		error_cmd_not_found(cmd->cmd_arr[0]);
		ft_free_2d(path_cmds);
		ft_free(found_path);
		minishell->exit_code = 127;
		exit_shell(minishell);
	}
}

// Executes a built-in command if part of a pipeline
// & needs exit to copy behavior from external command execution (execve),
// otherwise runs an external command.
// Note: Piped builtins lose their effect on the shell (bash).
void	execute_cmd_or_builtin_wpipe(t_cmd *cmd, t_minishell *minishell)
{
	if (is_builtin(cmd) == 1 && minishell->list_cmd->size > 1)
	{
		if (execute_builtin(cmd, minishell) == 0)
			minishell->exit_code = 1;
		else
			minishell->exit_code = 0;
		exit_shell(minishell);
	}
	else if (!(is_builtin(cmd)))
	{
		execution(cmd, minishell);
	}
}

// Checks if command is a builtin & only command in the list (no pipe involved).
// Note: [Some builtins modify the shell's environment 
//  --> If in child process, their effects won’t persist in parent.]
// If so, it handles I/O redirection and executes the builtin.
void	execute_builtin_without_pipe(t_cmd *cmd, t_minishell *minishell)
{
	if (is_builtin(cmd) == 1 && minishell->list_cmd->size == 1)
	{
		if (setup_redirections(cmd, minishell) == 1)
		{
			if (execute_builtin(cmd, minishell) == 0)
				minishell->exit_code = 1;
			else
				minishell->exit_code = 0;
		}
	}
}
