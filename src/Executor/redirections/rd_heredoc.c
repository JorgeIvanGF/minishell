#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

// Reads input lines from standard input and writes them to a heredoc file
// until a specified delimiter is encountered.
/*
Appends a newline to the delimiter for comparison purposes,
displays a prompt ("> ") before each line of input, 
and writes all input to specified file descriptor until delimiter is encountered.
Memory is freed and the file descriptor is closed upon completion.
*/
void	write_heredoc_to_file(int fd_heredoc_file, char *delimiter,
		t_minishell *minishell)
{
	char	*line;

	delimiter = ft_strjoin(delimiter, "\n");
	while (1)
	{
		write(minishell->og_stdout_fd, "> ", 2);
		line = get_next_line(minishell->og_stdin_fd);
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_free(line);
			break ;
		}
		write(fd_heredoc_file, line, ft_strlen(line));
		ft_free(line);
	}
	ft_free(delimiter);
	close(fd_heredoc_file);
}

// handles heredoc redirection by opening temporary file for writing, 
// storing user input until delimiter is encountered,
// then reopening file for reading and returning its file descriptor.
int	redirect_heredoc(char *delimiter, t_minishell *minishell)
{
	int	fd_heredoc_file;
	int	fd_heredoc_file2;

	if (open_file_check_rdhoc_wr(&fd_heredoc_file) == -1)
		return (-1);
	write_heredoc_to_file(fd_heredoc_file, delimiter, minishell);
	if (open_file_check_rdhoc_rd(&fd_heredoc_file2) == -1)
		return (-1);
	return (fd_heredoc_file2);
}
