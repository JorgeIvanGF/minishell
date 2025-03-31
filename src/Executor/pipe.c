#include "execution.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Checks if command contains a pipe
int	has_pipe(t_cmd *cmd)
{
	if (cmd && cmd->next == NULL)
	{
		return (0);
	}
	return (1);
}

/*
For the child process, if a pipe is found, redirect output to the pipe.
Close the read end of the pipe.
*/
void	redirect_output_to_pipe(t_cmd *cmd, int fd[2])
{
	if (cmd->next == NULL)
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

/*
For the parent process, redirect input from the pipe (read end of the pipe).
Close the write end of the pipe.
*/
void	redirect_input_to_pipe(int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}
