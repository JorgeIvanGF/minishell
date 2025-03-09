#include "../../inc/minishell.h"
#include "execution.h"

int has_pipe(t_cmd *cmd) // if pipe found (1), or not (0)
{
	if (cmd->next == NULL)
	{
		return (0); // pipe not found
	}

	return (1); // pipe found
}

void setup_pipe(int fd[2]) // TOOD: delete (not needed)
{
    pipe(fd);
}

/*
redirection of pipe according to type of process. 
child process: if pipe found, output redirected to pipe, else pipe closed. 
parent process: input redirected to pipe. 
*/ 
void handle_pipe_redirection(t_cmd *cmd, int fd[2], int process_type)
{
	if (process_type == CHILD_PROCESS)
	{
		if(has_pipe(cmd) == 1)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else
		{
			close(fd[0]);
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
