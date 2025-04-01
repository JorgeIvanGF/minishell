#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

int		process_full_cmd_line(t_cmd *cmd, t_minishell *minishell);
void	handle_wait_and_exit_status(t_minishell *minishell, int id, \
		int *status);

/*
* Processes the command list by iterating through each command and executing it.
* -Returns ID -1 for built-ins executed in parent process (no child to wait for).
* Waits for child processes to complete if any were created (id != -1).
* Updates exit status based on the last command's result.
* Cleans up temporary heredoc files after command execution.
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
	// printf(GREEN"exit code = %d\n", minishell->exit_code); // TO DEBUG
	unlink("./src/Executor/redirections/heredocfile");
}

/*
* Handles the execution of a command,
* 	including managing pipe redirection and I/O redirection.
* Child process: executes the command,
*	either running a builtin or an external command,
* Parent process: sets up input redirection,
*	executes built-ins without pipes if necessary, and cleans up.
* Note: If last command, redirect_output_to_pipe will close pipe.
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
		enable_SIGQUIT_in_child();//NEW NEW NEW
		redirect_output_to_pipe(cmd, fd);
		check_and_setup_redirections(cmd, minishell);
		execute_cmd_or_builtin_wpipe(cmd, minishell);
	}
	else
		redirect_input_to_pipe(fd);
	return (id);
}

/*
* Handles multiple child processes.
* 1. Waits for last child [last ran command] to finish & stores exit status.
* 2. Waits for remaining [zombie] child processes to finish.
* 3. Checks how last process ended.
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
		print_signal_message(WTERMSIG(*status));//NEW NEW NEW
	}
	else if (WIFSTOPPED(*status))
		minishell->exit_code = 128 + WSTOPSIG(*status);
	else if (WIFCONTINUED(*status))
	{
	}
	setup_interactive_signals(); //SIGNALSNEW
}
