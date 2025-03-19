#include "../../inc/minishell.h"
#include "execution.h"
#include "signals.h"

void	execution(char **env, t_cmd *cmd) 
{
	char	*path;
	char	**path_cmds;
	char	*found_path;
	
	path = get_path(env);
	path_cmds = get_paths_cmds(path);
	found_path = find_path(path_cmds, cmd->cmd_arr[0]);
	if (execute(found_path, cmd, env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd_arr[0], 2);
		ft_putendl_fd(": command not found", 2);
		ft_free_2d(path_cmds);
		free(found_path);
		// minishell->exit_code = 127; // TODO: put minishell as input
		// // exit_shell();
		exit(127);
	}
}

int	execute_cmd(t_cmd *cmd, t_minishell *minishell)
{
	int	id;
	int fd[2];
	
	pipe(fd);
	setup_signals_non_interactive(); // SIGNALS: Ignore signals before fork
	id = fork();
	if (id == 0) 
	{
		setup_signals_default(); // SIGNALS: Reset signals to default in child
		if (!(is_builtin(cmd) == 1 && has_pipe(cmd) == 0)) 
		{
			handle_pipe_redirection(cmd, fd, CHILD_PROCESS); 
			if (redirecting_io(cmd) == 1) // TODO: recheck where to call (what if no file found?)
			{
				if (is_builtin(cmd) == 1) // pipe check: IF pipe found, go ahead (for builtins)
				{
					execute_builtin(cmd, minishell);
				}
				else 
				{
					execution(minishell->env, cmd);
				}
			}
		}
		exit(0); // TODO: line needs to be double checked bc of #
	}
	else 
	{
		handle_pipe_redirection(cmd, fd, PARENT_PROCESS); 
		if (is_builtin(cmd) == 1 && has_pipe(cmd) == 0) // pipe check: IF pipe not found, go ahead (for builtins) //
		{
			if (redirecting_io(cmd) == 1)
			{
				execute_builtin(cmd, minishell);
			}
		}
	}
	return(id);
}

void looping_through_list_commands(t_minishell *minishell) // TODO: change name of ft
{
	t_cmd *current;
	int status;
	int id;

	current = minishell->list_cmd->head;
	while(current != NULL)
	{ 
		id = execute_cmd(current, minishell); // alle fd redirection redirecten stdin, stdout
		current = current->next;
	}
		setup_signals_non_interactive(); // SIGNALS: Ignore signals during wait 
		waitpid(id,&status, 0); // TODO: change wait
		while (waitpid(-1, NULL, WNOHANG) != -1) //WUNTRACED
			;
		if (WIFEXITED(status))  // if child process terminated normally // updates minishell exit code/status from last ran command (paula if)
		{
			minishell->exit_code = WEXITSTATUS(status); // macro to extract exit code/status
			printf("Child exited with status: %d\n", minishell->exit_code); // for testing
		}

		setup_signals_interactive(); // SIGNALS: Reset signals to interactive mode */
		if (WIFSIGNALED(status)) // checks if the child process was terminated by a signal (instead of exiting normally)
		{
			// Returns the actual signal number that caused the termination.
			// If the signal that killed the child was SIGINT(ex. when Ctrl C pressed)
			if (WTERMSIG(status) == SIGINT) 
				g_signum = SIGINT; //set the global variable g_signum to SIGINT.
			else if (WTERMSIG(status) == SIGQUIT)
			{
				g_signum = SIGQUIT;
				write(2, "Quit (core dumped)\n", 19);
			}
		}
}

// go thru entire cmd list. if command found, execute w above function, if not, execution will handle
void checking_list_cmds_for_exec(t_minishell *minishell) // TODO: delete later
{
	t_cmd *current;
	int cmd_list_position;

	cmd_list_position = 1;
	current = minishell->list_cmd->head;
	while(current != NULL)  
	{
		printf("%d. COMMAND\n", cmd_list_position);
		execute_cmd(current, minishell);
		current = current->next;
		cmd_list_position++;
	}
}

int ft_execution (t_minishell *minishell)
{

	// list_cmds = init_list_commands(1, first_cmd, NULL); 
	print_list_commands(minishell->list_cmd);

//88888888888888888888888888888888888888888888888888888888888888888888 exec
	// saving original of stdin & stdout
	int copy_of_stdin_fd = dup(STDIN_FILENO);
	int copy_of_stdout_fd = dup(STDOUT_FILENO);

	// setup_signals_non_interactive(); // SIGNALS: Ignore signals during execution setup

	looping_through_list_commands(minishell); // going through list_cmds & checking for RD_IN & file
	// stdin & stdout has to be set back to its original TODO: (create ft for it later)
	dup2(copy_of_stdin_fd, STDIN_FILENO);
	close(copy_of_stdin_fd);
	dup2(copy_of_stdout_fd, STDOUT_FILENO);
	close(copy_of_stdout_fd);

	// setup_signals_interactive(); // SIGNALS: Reset signals to interactive mode


	// may be deleted: checking_list_cmds_for_exec(list_cmds, minishell->env); // goes thru cmd list and executes all cmds

	return (minishell->exit_code);
}
