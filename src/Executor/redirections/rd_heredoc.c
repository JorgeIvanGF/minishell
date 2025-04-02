/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:50:55 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 03:24:24 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// void	write_heredoc_to_file(int fd_heredoc_file, char *delimiter,
// 		t_minishell *minishell)
// {
// 	char	*line;

// 	delimiter = ft_strjoin(delimiter, "\n");
// 	while (1)
// 	{
// 		write(minishell->og_stdout_fd, "> ", 2);
// 		line = get_next_line(minishell->og_stdin_fd);
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			ft_free(line);
// 			break ;
// 		}
// 		write(fd_heredoc_file, line, ft_strlen(line));
// 		ft_free(line);
// 	}
// 	ft_free(delimiter);
// 	close(fd_heredoc_file);
// }

// *******************

void	write_heredoc_to_file(int fd_heredoc_file, char *delimiter,
	t_minishell *minishell)
{
char	*line;

delimiter = ft_strjoin(delimiter, "\n");
while (1)
{
	write(minishell->og_stdout_fd, "> ", 2);
	line = get_next_line(minishell->og_stdin_fd);

	// Fix: handle Ctrl+D / EOF
	if (!line)
		break;

	if (ft_strcmp(line, delimiter) == 0)
	{
		ft_free(line);
		break;
	}
	write(fd_heredoc_file, line, ft_strlen(line));
	ft_free(line);
}
ft_free(delimiter);
close(fd_heredoc_file);
}


// Handles heredoc redirection by opening temporary file for writing, 
// storing user input until delimiter is encountered,
// then reopening file for reading and returning its file descriptor.
// int	redirect_heredoc(char *delimiter, t_minishell *minishell)
// {
// 	int	fd_heredoc_file;
// 	int	fd_heredoc_file2;

// 	setup_heredoc_signals();
// 	if (open_file_check_rdhoc_wr(&fd_heredoc_file) == -1)
// 		return (-1);
// 	write_heredoc_to_file(fd_heredoc_file, delimiter, minishell);
// 	if (open_file_check_rdhoc_rd(&fd_heredoc_file2) == -1)
// 		return (-1);
// 	return (fd_heredoc_file2);
// }

// *******************

int	redirect_heredoc(char *delimiter, t_minishell *minishell)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	setup_heredoc_signals();
	if (pipe(pipe_fd) == -1)
		return (-1);

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); // Allow Ctrl+C to kill heredoc input
		close(pipe_fd[0]);       // Close unused read end
		write_heredoc_to_file(pipe_fd[1], delimiter, minishell);
		close(pipe_fd[1]);
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);       // Close write end in parent
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			minishell->exit_code = 1;
			close(pipe_fd[0]);
			return (-1); // Abort heredoc
		}
		return (pipe_fd[0]); // Use as input FD
	}
}
