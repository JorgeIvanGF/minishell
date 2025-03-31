#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

void	execution(t_cmd *cmd, t_minishell *minishell)
{
	char	*path;
	char	**path_cmds;
	char	*found_path;

	path = get_path(minishell->env);
	path_cmds = get_paths_cmds(path);
	found_path = find_path(path_cmds, cmd->cmd_arr[0]);
	if (execute(found_path, cmd, minishell->env) == -1)
	{
		error_cmd_not_found(cmd->cmd_arr[0]);
		ft_free_2d(path_cmds);
		//free(found_path);
		minishell->exit_code = 127;
		exit_shell(minishell);
	}
}

// Executes a built-in command if part of a pipeline, otherwise runs an external command.
void execute_cmd_or_builtin_wpipe(t_cmd *cmd, t_minishell *minishell)
{
	if (is_builtin(cmd) == 1 && minishell->list_cmd->size > 1)
	{
		execute_builtin(cmd, minishell);
	}
	else if (!(is_builtin(cmd)))
	{
		execution(cmd, minishell);
	}
}

/*
Checks if command is a builtin and the only command in the list (no pipe involved). 
If so, it handles I/O redirection and executes the builtin.
*/
void execute_builtin_without_pipe(t_cmd *cmd, t_minishell *minishell)
{ 
	if (is_builtin(cmd) == 1 && minishell->list_cmd->size == 1)
	{
		if (setup_redirections(cmd, minishell) == 1)
		{
			execute_builtin(cmd, minishell);
		}
	}
}

/*
Handles the execution of a command, including managing pipe redirection and I/O redirection. 
Child process: executes the command, either running a builtin or an external command, 
Parent process: sets up input redirection, executes built-ins without pipes if necessary, and cleans up. 
Note: If last command, redirect_output_to_pipe will close pipe.
*/
int	process_full_cmd_line(t_cmd *cmd, t_minishell *minishell)
{
	int	id;
	int	fd[2];

	setup_signals_non_interactive();
	if (is_builtin(cmd) == 1 && minishell->list_cmd->size == 1)
	{
		execute_builtin_without_pipe(cmd, minishell);
		return (-1);
	}
	if (pipe(fd) == -1)
	{
		minishell->exit_code = 1; // TODO: change exit code to input exit_shell(minishell, 1) everywehre
		exit_shell(minishell);
	}
	id = fork();
	if (id == 0)
	{
		setup_signals_default();
		redirect_output_to_pipe(cmd, fd);
		check_and_setup_redirections(cmd, minishell);
		execute_cmd_or_builtin_wpipe(cmd, minishell);
	}
	else
		redirect_input_to_pipe(fd);
	return (id);
}

/*
Handles multiple child processes: waits for each process to finish, checks its exit status, 
and updates the minishell's exit code accordingly, specifically for last ran command. 
*/
void	handle_wait_and_exit_status(t_minishell *minishell, int id, int *status)
{
	waitpid(id, status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(status))
	{
		minishell->exit_code = WEXITSTATUS(status);
	}
}

/*
Iterates through list of commands, processes each command, and manages signals during execution. 
It waits for all processes to finish, handles their exit status, and ensures proper signal handling.
*/
void	iterate_and_execute_cmd_list(t_minishell *minishell)
{
	t_cmd	*current;
	int		status;
	int		id;

	current = minishell->list_cmd->head;
	while (current != NULL)
	{
		id = process_full_cmd_line(current, minishell);
		current = current->next;
	}
	setup_signals_non_interactive();
	handle_wait_and_exit_status(minishell, id, &status);
	unlink("./src/Executor/redirections/viktoria1");
	setup_signals_interactive();
	handle_signal_termination(status);
}

// Save original file descriptors of STDIN and STDOUT
void	save_io_fds(t_minishell *minishell)
{
	minishell->og_stdin_fd = dup(STDIN_FILENO);
	minishell->og_stdout_fd = dup(STDOUT_FILENO);
}

// Restore STDIN and STDOUT to their original file descriptors
void	restore_io(t_minishell *minishell)
{
	dup2(minishell->og_stdin_fd, STDIN_FILENO);
	close(minishell->og_stdin_fd);
	dup2(minishell->og_stdout_fd, STDOUT_FILENO);
	close(minishell->og_stdout_fd);
}

int	ft_execution(t_minishell *minishell)
{
	// print_list_commands(minishell->list_cmd);
	save_io_fds(minishell);
	iterate_and_execute_cmd_list(minishell);
	restore_io(minishell);
	return (minishell->exit_code);
}
