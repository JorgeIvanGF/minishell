#include "../../inc/minishell.h"
#include "execution.h"
#include "signals.h"

void	execution(char **env, t_cmd *cmd) 
{
	char	*path;
	char	**path_cmds;
	char	*found_path;
	char 	*saved_cmd;

	saved_cmd = ft_strdup(cmd->cmd_arr[0]);  // create a copy b4 freeing
	if (!saved_cmd)
		exit(1);
	path = get_path(env);
	path_cmds = get_paths_cmds(path);
	found_path = find_path(path_cmds, cmd->cmd_arr[0]);
	if (execute(found_path, cmd, env) == -1)
	{
		ft_free_2d(path_cmds);
		free(found_path);
		write(2, "minishell: command not found: ", 30);
		write(2, saved_cmd, ft_strlen(saved_cmd));
		write(2, "\n", 1);
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

// New function to handle signal termination:
// Checks if the child process was terminated by a signal (instead of normally)
// Returns the actual signal number that caused the termination.
// If the signal that killed the child was SIGINT(ex. when Ctrl C pressed)
// -> set the global variable g_signum to SIGINT.
void handle_signal_termination(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT) 
			g_signum = SIGINT;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			g_signum = SIGQUIT;
			write(2, "Quit (core dumped)\n", 19);
		}
	}
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
		waitpid(id,&status, 0);
		while (waitpid(-1, NULL, WNOHANG) != -1) //WUNTRACED
			;
		setup_signals_interactive(); // SIGNALS: Reset signals to interactive mode
		handle_signal_termination(status); // SIGNALS: Check signal termination
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
	// print_list_commands(minishell->list_cmd);

//88888888888888888888888888888888888888888888888888888888888888888888 exec
	// saving original of stdin & stdout
	int copy_of_stdin_fd = dup(STDIN_FILENO);
	int copy_of_stdout_fd = dup(STDOUT_FILENO);

	setup_signals_non_interactive(); // SIGNALS: Ignore signals during execution setup

	looping_through_list_commands(minishell); // going through list_cmds & checking for RD_IN & file
	// stdin & stdout has to be set back to its original TODO: (create ft for it later)
	dup2(copy_of_stdin_fd, STDIN_FILENO);
	close(copy_of_stdin_fd);
	dup2(copy_of_stdout_fd, STDOUT_FILENO);
	close(copy_of_stdout_fd);

	setup_signals_interactive(); // SIGNALS: Reset signals to interactive mode


	// may be deleted: checking_list_cmds_for_exec(list_cmds, minishell->env); // goes thru cmd list and executes all cmds

	return (minishell->exit_code);
}
