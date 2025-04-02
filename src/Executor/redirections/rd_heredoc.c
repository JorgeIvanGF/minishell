/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:50:55 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/03 01:08:03 by pauladretta      ###   ########.fr       */
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
void	write_heredoc_to_file(int fd_heredoc_file, char *delimiter,
		t_minishell *minishell)
{
	char	*line;
	delimiter = ft_strjoin(delimiter, "\n");
	while (1)
	{
		write(minishell->og_stdout_fd, "> ", 2);
		line = get_next_line(minishell->og_stdin_fd);
		if (line == NULL)
		{
			break;
		}
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

// *******************

// void	write_heredoc_to_file(int fd_heredoc_file, char *delimiter,
// 	t_minishell *minishell)
// {
// char	*line;

// delimiter = ft_strjoin(delimiter, "\n");
// while (1)
// {
// 	write(minishell->og_stdout_fd, "> ", 2);
// 	line = get_next_line(minishell->og_stdin_fd);

// 	// Fix: handle Ctrl+D / EOF
// 	if (!line)
// 		break;

// 	if (ft_strcmp(line, delimiter) == 0)
// 	{
// 		ft_free(line);
// 		break;
// 	}
// 	write(fd_heredoc_file, line, ft_strlen(line));
// 	ft_free(line);
// }
// ft_free(delimiter);
// close(fd_heredoc_file);
// }


// Handles heredoc redirection by opening temporary file for writing, 
// storing user input until delimiter is encountered,
// then reopening file for reading and returning its file descriptor.
// exit (3) [personalized] if ctrl d
// exit (4) [personalized] if ctrl c (write_heredoc_to_file)
int	handle_heredoc(t_rdir *hdoc_rdir, char *delimiter, t_minishell *minishell, int hdoc_counter)
{
	int	fd_heredoc_file;
	char *heredoc_newname;
	int id;
	int status;

	heredoc_newname = open_file_check_rdhoc_wr(&fd_heredoc_file, hdoc_counter);
	if (heredoc_newname == NULL)
		return (-1);
	id = fork();
	if(id == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		setup_heredoc_signals();
		write_heredoc_to_file(fd_heredoc_file, delimiter, minishell);
		exit(3);
	}
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		minishell->exit_code = WEXITSTATUS(status);
	ft_free(hdoc_rdir->name);
	hdoc_rdir->name = heredoc_newname;
	return (minishell->exit_code);
}

// *******************

// int	redirect_heredoc(char *delimiter, t_minishell *minishell)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;
// 	int		status;

// 	setup_heredoc_signals();
// 	if (pipe(pipe_fd) == -1)
// 		return (-1);

// 	pid = fork();
// 	if (pid == -1)
// 		return (-1);

// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL); // Allow Ctrl+C to kill heredoc input
// 		close(pipe_fd[0]);       // Close unused read end
// 		write_heredoc_to_file(pipe_fd[1], delimiter, minishell);
// 		close(pipe_fd[1]);
// 		exit(0);
// 	}
// 	else
// 	{
// 		close(pipe_fd[1]);       // Close write end in parent
// 		waitpid(pid, &status, 0);
// 		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 		{
// 			minishell->exit_code = 1;
// 			close(pipe_fd[0]);
// 			return (-1); // Abort heredoc
// 		}
// 		return (pipe_fd[0]); // Use as input FD
// 	}
// }
