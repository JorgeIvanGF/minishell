#include "minishell.h"
#include "execution.h"
#include "parsing.h"
#include "signals.h"

int	redirect_stdin(t_cmd *cmd);
int	redirect_stdout(t_cmd *cmd);
int	redirect_heredoc(char *delimiter);

// Redirect both STDIN and STDOUT based on the redirection types in the command
int	redirect_io(t_cmd *cmd)
{	
	return(redirect_stdin(cmd) && redirect_stdout(cmd));
}

void redirect_stdin_to_file(int fd_infile)
{
	dup2(fd_infile, STDIN_FILENO); 
	close(fd_infile);
}

// Redirect STDIN from specified file(s) based on the redirection type in cmd
int	redirect_stdin(t_cmd *cmd)
{
	t_rdir	*current;
	int		fd_infile;

	if(cmd && cmd->list_rdir && cmd->list_rdir->head)
	{
		current = cmd->list_rdir->head;
		while(current != NULL)
		{
			if (current->type == RD_IN)
			{
				if (open_file_check_RDIN(current->name, &fd_infile) == -1)
					return (0);
				redirect_stdin_to_file(fd_infile);
			}
			else if (current->type == RD_HDOC && current->name)
			{
				fd_infile = redirect_heredoc(current->name);
				if (fd_infile == -1)
					return (0);
				redirect_stdin_to_file(fd_infile);
			}
			current = current->next;
		}
	}
	return (1);
}

int	check_io(t_cmd *cmd)
{
	t_rdir	*current;
	int		fd_file;

	if(cmd && cmd->list_rdir && cmd->list_rdir->head)
	{
		current = cmd->list_rdir->head;
		while(current != NULL)
		{
			if (current->type == RD_IN)
			{
				if (open_file_check_RDIN(current->name, &fd_file) == -1)
					return (-1);
				close(fd_file);
			}
			else if (current->type == RD_OUT)
			{
				if (open_file_check_RD_OUT(current->name, &fd_file) == -1)
					return (-1);
				close (fd_file);
			}
			else if (current->type == RD_APND)
			{
				if (open_file_check_RD_APND(current->name, &fd_file) == -1)
						return (-1);
				close (fd_file);
			}
			current = current->next;
		}
	}
	return (1);
}

void redirect_stdout_to_file(int fd_outfile)
{
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
}

// Redirect STDOUT to specified file(s) based on the redirection type in cmd
int	redirect_stdout(t_cmd *cmd)
{
	t_rdir	*current;
	int		fd_outfile;

	if (cmd && cmd->list_rdir && cmd->list_rdir->head)
	{
		current = cmd->list_rdir->head;
		while(current != NULL)
		{
			if (current->type == RD_OUT)
			{
				if (open_file_check_RD_OUT(current->name, &fd_outfile) == -1)
					return (0);
				redirect_stdout_to_file(fd_outfile);
			}
			else if (current->type == RD_APND)
			{
				if (open_file_check_RD_APND(current->name, &fd_outfile) == -1)
					return (0);
				redirect_stdout_to_file(fd_outfile);
			}
			current = current->next;
		}
	}
	return (1);
}

int redirect_heredoc(char *delimiter)
{
	int		fd_heredoc_file;
	int		fd_heredoc_file2;
	char	*line;
	write(2, delimiter, ft_strlen(delimiter));
	fd_heredoc_file = open("./src/Executor/redirections/viktoria1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_heredoc_file == -1)
	{
		error_heredoc();
		return (-1);
	}
	delimiter = ft_strjoin(delimiter, "\n"); // bc line has new line
	while (1)
	{
		write (1, "> ", 2); // TODO: bring & change to original stdinput (from main)
		line = get_next_line(0);
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
	fd_heredoc_file2 = open("./src/Executor/redirections/viktoria1", O_RDONLY);
	if (fd_heredoc_file2 == -1)
	{
		error_heredoc();
		return (-1);
	}
	return (fd_heredoc_file2);
}
