#include "minishell.h"
#include "execution.h"
#include "parsing.h"
#include "signals.h"

int	setup_redirections(t_cmd *cmd, t_minishell *minishell);
int handle_input_redirection(t_rdir	*current, t_minishell *minishell);
int handle_output_redirection(t_rdir *current);

// Redirect both STDIN and STDOUT based on the redirection types in the command
void	check_and_setup_redirections(t_cmd *cmd, t_minishell *minishell)
{	
	if (setup_redirections(cmd, minishell) == 0)
	{
		minishell->exit_code = 1;
		 exit_code_num = minishell->exit_code ; //TODO: delete
		exit_shell(minishell);
	}
}

// Redirect STDIN & STDOUT from specified file(s) based on the redirection type in cmd
int	setup_redirections(t_cmd *cmd, t_minishell *minishell)
{
	t_rdir	*current;

	if(cmd && cmd->list_rdir && cmd->list_rdir->head)
	{
		current = cmd->list_rdir->head;
		while(current != NULL)
		{
			if (handle_input_redirection(current, minishell) == 0)
			{
				return (0);
			}
			else if (handle_output_redirection(current) == 0)
			{
				return (0);
			}
			current = current->next;
		}
	}
	return (1);
}

// Redirects STDIN by opening specified file (<) or processing a heredoc (<<)
int handle_input_redirection(t_rdir	*current, t_minishell *minishell)
{
	int		fd_file;

	if (current->type == RD_IN)
	{
		if (open_file_check_RDIN(current->name, &fd_file) == -1)
			return (0);
		redirect_stdin_to_file(fd_file);
	}
	else if (current->type == RD_HDOC && current->name)
	{
		fd_file = redirect_heredoc(current->name, minishell);
		if (fd_file == -1)
			return (0);
		redirect_stdin_to_file(fd_file);
	}
	return (1);
}

// Redirects STDOUT by opening specified file in either truncate (>) or append (>>) mode
int handle_output_redirection(t_rdir *current)
{
	int		fd_file;

	if (current->type == RD_OUT)
	{
		if (open_file_check_RD_OUT(current->name, &fd_file) == -1)
			return (0);
		redirect_stdout_to_file(fd_file);
	}
	else if (current->type == RD_APND)
	{
		if (open_file_check_RD_APND(current->name, &fd_file) == -1)
			return (0);
		redirect_stdout_to_file(fd_file);
	}
	return (1);
}

// Reads input lines from standard input and writes them to a heredoc file
// until a specified delimiter is encountered.
/*
The function appends a newline to the delimiter for comparison purposes,
displays a prompt ("> ") before each line of input, and writes all input
to the specified file descriptor until the delimiter is encountered.
Memory is freed and the file descriptor is closed upon completion.
*/
void write_heredoc_to_file(int fd_heredoc_file, char *delimiter, t_minishell *minishell)
{
	char	*line;

	delimiter = ft_strjoin(delimiter, "\n"); // bc line has new line
	while (1)
	{
		write (minishell->og_stdout_fd, "> ", 2);
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

int redirect_heredoc(char *delimiter, t_minishell *minishell)
{
	int		fd_heredoc_file;
	int		fd_heredoc_file2;

	if (open_file_check_RD_HOC_WR(&fd_heredoc_file) == -1)
		return (-1);

	write_heredoc_to_file(fd_heredoc_file, delimiter, minishell);

	if (open_file_check_RD_HOC_RD(&fd_heredoc_file2) == -1)
		return (-1);
	return (fd_heredoc_file2);
}
