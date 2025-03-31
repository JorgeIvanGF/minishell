#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

// open file check RD_IN
int open_file_check_RDIN(char *rdir_name, int *fd_infile)
{
	*fd_infile = open(rdir_name, O_RDONLY);
	if (*fd_infile == -1)
	{
		error_no_file_directory(rdir_name);
		return (-1);
	}

	return (1);
}

// open file check RD_HOC 1
// opens or creates file in write mode (truncating if it exists);
int open_file_check_RD_HOC_WR(int *fd_heredoc_file)
{
    *fd_heredoc_file = open("./src/Executor/redirections/heredocfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_heredoc_file == -1)
	{
		error_heredoc();
		return (-1);
	}

    return (1);
}

// open file check RD_HOC 2
// opens file in read mode
int open_file_check_RD_HOC_RD(int *fd_heredoc_file2)
{
    *fd_heredoc_file2 = open("./src/Executor/redirections/heredocfile", O_RDONLY);
	if (*fd_heredoc_file2 == -1)
	{
		error_heredoc();
		return (-1);
	}

    return (1);
}

// open file check RD_OUT
int open_file_check_RD_OUT(char *rdir_name, int *fd_outfile)
{
    *fd_outfile = open(rdir_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*fd_outfile == -1)
    {
        error_no_file_directory(rdir_name);
        return (-1);
    }

    return (1);
}

// open file check RD_APND
int open_file_check_RD_APND(char *rdir_name, int *fd_outfile)
{
    *fd_outfile = open(rdir_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (*fd_outfile == -1)
    {
        error_no_file_directory(rdir_name);
        return (-1);
    }

    return (1);
}
