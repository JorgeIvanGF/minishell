#include "minishell.h"
#include "execution.h"
#include "parsing.h"
#include "signals.h"

void redirect_stdin_to_file(int fd_infile)
{
	dup2(fd_infile, STDIN_FILENO); 
	close(fd_infile);
}

void redirect_stdout_to_file(int fd_outfile)
{
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
}
