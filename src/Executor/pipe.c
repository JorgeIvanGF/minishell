#include "minishell.h"
#include "execution.h"

// Checks if command contains a pipe
int has_pipe(t_cmd *cmd) 
{
	if (cmd && cmd->next == NULL)
	{
		return (0); 
	}
	
	return (1); 
}

/*
Handle I/O redirection to/from a pipe based on process type
- For the child process, if a pipe is found, redirect output to the pipe. Close the read end of the pipe.
- For the parent process, redirect input from the pipe (read end of the pipe). Close the write end of the pipe.
*/
void handle_pipe_redirection(t_cmd *cmd, int fd[2], int process_type)
{
	if (process_type == CHILD_PROCESS)
	{
		// if(has_pipe(cmd) == 1)
		// {
		// 	close(fd[0]);
		// 	dup2(fd[1], STDOUT_FILENO);
		// 	close(fd[1]);
		// }
		// else
		// {
		// 	close(fd[0]);
		// 	close(fd[1]);
		// }

		if(cmd->next == NULL) // new // TODO: compare with above
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
	}
	
	else if (process_type == PARENT_PROCESS)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
