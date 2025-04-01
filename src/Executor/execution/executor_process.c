#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

void	handle_wait_and_exit_status(t_minishell *minishell, int id, int *status);
void	iterate_and_execute_cmd_list(t_minishell *minishell);

/*
Handles the execution of a command,
	including managing pipe redirection and I/O redirection.
Child process: executes the command,
	either running a builtin or an external command,
Parent process: sets up input redirection,
	executes built-ins without pipes if necessary, and cleans up.
Note: If last command, redirect_output_to_pipe will close pipe.
*/
int	process_full_cmd_line(t_cmd *cmd, t_minishell *minishell)
{
	int	id;
	int	fd[2];

	if (is_builtin(cmd) == 1 && minishell->list_cmd->size == 1)
	{
		execute_builtin_without_pipe(cmd, minishell);
		return (-1);
	}
	if (pipe(fd) == -1)
	{
		minishell->exit_code = 1;
		exit_shell(minishell);
	}
	id = fork();
	if (id == 0)
	{
		setup_exec_signals(); //SIGNALSNEW
		redirect_output_to_pipe(cmd, fd);
		check_and_setup_redirections(cmd, minishell);
		execute_cmd_or_builtin_wpipe(cmd, minishell);
	}
	else
		redirect_input_to_pipe(fd);
	return (id);
}

/*
Handles multiple child processes: waits for each process to finish,
	checks its exit status,
and updates the minishell's exit code accordingly,
	specifically for last ran command.
*/
void	handle_wait_and_exit_status(t_minishell *minishell, int id, int *status)
{
	waitpid(id, &(*status), 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(*status))
		minishell->exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		minishell->exit_code = 128 + WTERMSIG(*status);
		if (WCOREDUMP(*status))
		{
		}
	}
	else if (WIFSTOPPED(*status))
		minishell->exit_code = 128 + WSTOPSIG(*status);
	else if (WIFCONTINUED(*status))
	{
	}
	setup_interactive_signals(); //SIGNALSNEW
}

/*
Iterates through list of commands, processes each command,
	and manages signals during execution.
It waits for all processes to finish, handles their exit status,
	and ensures proper signal handling.
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
	if (id != -1)
		handle_wait_and_exit_status(minishell, id, &status);
	//printf(GREEN"exit code = %d\n", minishell->exit_code); // TO DEBUG
	unlink("./src/Executor/redirections/heredocfile");
}
