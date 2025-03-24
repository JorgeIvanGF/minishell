#include "minishell.h"
#include "execution.h"
#include "signals.h"
#include "parsing.h"

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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd_arr[0], 2);
		ft_putendl_fd(": command not found", 2);
		ft_free_2d(path_cmds);
		free(found_path);
		minishell->exit_code = 127;
		exit_shell(minishell);
	}
}

int	execute_cmd(t_cmd *cmd, t_minishell *minishell)
{
	int	id;
	int fd[2];
	
	pipe(fd);
	setup_signals_non_interactive(); // SIGNALS: Ignore signals before fork
	id = fork();
	// printf("id =%d\n", id); // for testing
	if (id == 0) 
	{
		setup_signals_default(); // SIGNALS: Reset signals to default in child
		
		// handle_pipe_redirection(cmd, fd, CHILD_PROCESS); 
		if(cmd->next == NULL)
		{
			close(fd[0]);
			close(fd[1]);
		}
		else
		{
			
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		
			if (redirect_io(cmd) == 1) // TODO: recheck where to call (what if no file found?)
			{
				if (is_builtin(cmd) == 1) // pipe check: IF pipe found, go ahead (for builtins)
				{
					execute_builtin(cmd, minishell);
				}
				else 
				{
					execution(cmd, minishell);
				}
			}
		
		minishell->exit_code = 127;
		exit_shell(minishell);
	}
	else 
	{
		// handle_pipe_redirection(cmd, fd, PARENT_PROCESS); 
		
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (is_builtin(cmd) == 1 && minishell->list_cmd->size == 1) // TODO: redo (eazy) m
		{
			if (redirect_io(cmd) == 1)
			{
				execute_builtin(cmd, minishell);
			}
		}
	}

	return (id);
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
	waitpid(id, &status, 0); // TOOD: put wait stuff in one sept ft to call here?
	while(wait(NULL) != -1) 
		;
	
	if (WIFEXITED(status))  // if child process terminated normally // updates minishell exit code/status from last ran command (paula if)
	{
		minishell->exit_code = WEXITSTATUS(status); // macro to extract exit code/status
		// printf("Child exited with status: %d\n", minishell->exit_code); // for testing
	}

	setup_signals_interactive(); // SIGNALS: Reset signals to interactive mode */
	handle_signal_termination(status); // SIGNALS: Check signal termination
}

// Save original file descriptors of STDIN and STDOUT
// void save_io_fds(int *stdin_fd_copy, int *stdout_fd_copy)
// {
// 	*stdin_fd_copy = dup(STDIN_FILENO);
// 	*stdout_fd_copy = dup(STDOUT_FILENO);
// }

// // Restore STDIN and STDOUT to their original file descriptors
// void restore_io(int stdin_fd_copy, int stdout_fd_copy)
// {
// 	dup2(stdin_fd_copy, STDIN_FILENO);
// 	close(stdin_fd_copy);
// 	dup2(stdout_fd_copy, STDOUT_FILENO);
// 	close(stdout_fd_copy);
// }

int ft_execution(t_minishell *minishell) // TODO: as main exec ft, have in one file, and seperate rest above
{
	int stdin_fd_copy;
	int stdout_fd_copy;

	print_list_commands(minishell->list_cmd);

	// save_io_fds(&stdin_fd_copy, &stdout_fd_copy);
	stdin_fd_copy = dup(STDIN_FILENO);
	stdout_fd_copy = dup(STDOUT_FILENO);

	looping_through_list_commands(minishell); // going through list_cmds & checking for RD_IN & file

	// restore_io(stdin_fd_copy, stdout_fd_copy);
	dup2(stdin_fd_copy, STDIN_FILENO);
	close(stdin_fd_copy);
	dup2(stdout_fd_copy, STDOUT_FILENO);
	close(stdout_fd_copy);

	return (minishell->exit_code);
}
