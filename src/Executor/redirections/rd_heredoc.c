/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:50:55 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/03 20:54:51 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

int		find_heredoc(t_minishell *minishell, t_cmd *cmd, int *hdoc_counter);
int		handle_heredoc(t_rdir *hdoc_rdir, char *delimiter,
			t_minishell *minishell, int hdoc_counter);
void	write_heredoc_to_file(int fd_heredoc_file, char *delimiter,
			t_minishell *minishell);

// Iterates through the command list to find and process heredocs (`<<`).
// HDOC interrupted with signals:
// - Sets exit code to 1 (4) if signal ctrl c is received
// - Sets exit code to 0 (3) if signal ctrl d is received 
int	check_heredoc(t_minishell *minishell)
{
	t_cmd	*current;
	int		hdoc_counter;
	int		hdoc_ps_exit_code;

	hdoc_ps_exit_code = 0;
	hdoc_counter = 0;
	current = minishell->list_cmd->head;
	while (current != NULL)
	{
		hdoc_ps_exit_code = find_heredoc(minishell, current, &hdoc_counter);
		current = current->next;
	}
	if (hdoc_ps_exit_code == 4)
		minishell->exit_code = 1;
	if (hdoc_ps_exit_code == 3)
		minishell->exit_code = 0;
	return (hdoc_ps_exit_code);
}

// Scans a command's redirections to detect heredocs (`<<`).  
// Calls `handle_heredoc()` for each heredoc found and tracks the count.
int	find_heredoc(t_minishell *minishell, t_cmd *cmd, int *hdoc_counter)
{
	t_rdir	*current;
	int		hdoc_ps_exit_code;

	current = cmd->list_rdir->head;
	hdoc_ps_exit_code = 0;
	while (current != NULL)
	{
		if (current->type == RD_HDOC)
		{
			(*hdoc_counter)++;
			hdoc_ps_exit_code = handle_heredoc(current, current->name,
					minishell, *hdoc_counter);
		}
		current = current->next;
	}
	return (hdoc_ps_exit_code);
}

// Processes heredoc redirection by creating temporary file for writing,
// storing user input until delimiter is encountered.
// exit (3) [personalized] if ctrl d
// exit (4) [personalized] if ctrl c (write_heredoc_to_file)
// Heredoc name in redirection structure is replaced with temporary file name.
// Forking due to signals to preserve shell's state.
int	handle_heredoc(t_rdir *hdoc_rdir, char *delimiter, t_minishell *minishell,
		int hdoc_counter)
{
	int		fd_heredoc_file;
	char	*heredoc_newname;
	int		id;
	int		status;

	heredoc_newname = open_file_check_rdhoc_wr(&fd_heredoc_file, hdoc_counter);
	if (heredoc_newname == NULL)
		return (-1);
	id = fork();
	if (id == 0)
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
			break ;
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

// Cleans up by removing all temporary heredoc files after execution
// To do so, for each command, it loops through its redirections for HDOC
void	unlink_hdoc_files(t_lst_cmd *list_cmd)
{
	t_cmd	*current_cmd;
	t_rdir	*current_rdir;

	current_cmd = list_cmd->head;
	while (current_cmd != NULL)
	{
		current_rdir = current_cmd->list_rdir->head;
		while (current_rdir != NULL)
		{
			if (current_rdir->type == RD_HDOC)
			{
				unlink(current_rdir->name);
			}
			current_rdir = current_rdir->next;
		}
		current_cmd = current_cmd->next;
	}
}
