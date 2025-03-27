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
		free(found_path);
		minishell->exit_code = 127;
		exit_shell(minishell);
	}
}

// Executes a built-in command if part of a pipeline, otherwise runs an external command.
void execute_cmd_or_builtin_wpipe(t_cmd *cmd, t_minishell *minishell)
{
	if (is_builtin(cmd) == 1 && minishell->list_cmd->size > 1)
	{
		write (2, "builtin executed if pipe\n", 25);
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
		if (redirect_io(cmd) == 1)
		{
			write (2, "builtin executed if NO pipe\n", 28);
			execute_builtin(cmd, minishell);
		}
	}
}

/*
Handles the execution of a command, including managing pipe redirection and I/O redirection. 
Child process: executes the command, either running a builtin or an external command, 
Parent process: sets up input redirection, executes built-ins without pipes if necessary, and cleans up. 
*/
int	process_full_cmd_line(t_cmd *cmd, t_minishell *minishell)
{
	int	id;
	int	fd[2];

	pipe(fd);
	setup_signals_non_interactive();
	id = fork();
	if (id == 0)
	{
		setup_signals_default();
		redirect_output_to_pipe(cmd, fd);
		if (redirect_io(cmd) == 1)
		{
			execute_cmd_or_builtin_wpipe(cmd, minishell);
		}
		minishell->exit_code = 127;
		exit_shell(minishell);
	}
	else
	{
		redirect_input_to_pipe(fd);
		unlink("viktoria1"); // loschen von erstellen heredoc des childes
		execute_builtin_without_pipe(cmd, minishell);
		unlink("viktoria1"); // loschen von erstellen heredoc des parents
	}
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
	handle_wait_and_exit_status(minishell, id, &status); // TODO: id?
	setup_signals_interactive();
	handle_signal_termination(status);
}

// Save original file descriptors of STDIN and STDOUT
void	save_io_fds(int *stdin_fd_copy, int *stdout_fd_copy)
{
	*stdin_fd_copy = dup(STDIN_FILENO);
	*stdout_fd_copy = dup(STDOUT_FILENO);
}

// Restore STDIN and STDOUT to their original file descriptors
void	restore_io(int stdin_fd_copy, int stdout_fd_copy)
{
	dup2(stdin_fd_copy, STDIN_FILENO);
	close(stdin_fd_copy);
	dup2(stdout_fd_copy, STDOUT_FILENO);
	close(stdout_fd_copy);
}

int	ft_execution(t_minishell *minishell) // TODO: as main exec ft, have in one file, and seperate rest above
{
	int	stdin_fd_copy;
	int	stdout_fd_copy;

	// print_list_commands(minishell->list_cmd);
	save_io_fds(&stdin_fd_copy, &stdout_fd_copy);
	iterate_and_execute_cmd_list(minishell);
	restore_io(stdin_fd_copy, stdout_fd_copy);
	return (minishell->exit_code);
}
