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
	return (redirect_stdin(cmd) && redirect_stdout(cmd)); // TODO: memorize 
}

// Redirect STDIN from specified file(s) based on the redirection type in cmd
int	redirect_stdin(t_cmd *cmd)
{
	t_rdir	*current;
	int		fd_infile;

	// fd_infile = 1;
	if(cmd && cmd->list_rdir && cmd->list_rdir->head)
	{
		current = cmd->list_rdir->head;
		while(current != NULL)
		{
			if (current->type == RD_IN) // go thru all rdin first and if all their are able to open, execute 
			{
				fd_infile = open(current->name, O_RDONLY);
				if (fd_infile == -1)
				{
					error_no_file_directory(current->name);
					return (-1);
				}
				else
				{
					dup2(fd_infile, STDIN_FILENO); 
					close(fd_infile);
				}
			}
			else if (current->type == RD_HDOC && current->name)
			{
				fd_infile = redirect_heredoc(current->name);
				if (fd_infile == -1)
				{
					return (-1);
				}
				else
				{
					dup2(fd_infile, STDIN_FILENO); 
					close(fd_infile);
				}
			}
			current = current->next;
		}
	}
	return (1);
}

// Redirect STDOUT to specified file(s) based on the redirection type in cmd
int	redirect_stdout(t_cmd *cmd)
{
	t_rdir	*current;
	int		fd_outfile;

	if(cmd && cmd->list_rdir && cmd->list_rdir->head)
	{
		current = cmd->list_rdir->head;
		while(current != NULL)
		{
			if (current->type == RD_OUT)
			{
				fd_outfile = open(current->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd_outfile == -1)
				{
					error_no_file_directory(current->name);
					return (-1);
				}
				else
				{
					dup2(fd_outfile, STDOUT_FILENO);
					close(fd_outfile);
				}
			}
			else if (current->type == RD_APND)
			{
				fd_outfile = open(current->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd_outfile == -1)
				{
					error_no_file_directory(current->name);
					return (-1);
				}
				else
				{
					dup2(fd_outfile, STDOUT_FILENO);
					close(fd_outfile);
				}
			}
			current = current->next;
		}
	}
	return (1);
}

int redirect_heredoc(char *delimiter) // TODO: fix - delimiter not closing it once typed // TODO: file should open hidden
{
	int		heredoc;
	int		heredoc2;
	char	*line;

	heredoc = open("viktoria1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc == -1)
	{
		error_heredoc();
		return (-1);
	}
	delimiter = ft_strjoin(delimiter, "\n"); // bc line has new line
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(0);
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_free(line);
			break ;
		}
		write(heredoc, line, ft_strlen(line));
		ft_free(line);
	}
	ft_free(delimiter);
	close(heredoc);
	heredoc2 = open("viktoria1", O_RDONLY);
	if (heredoc2 == -1)
	{
		error_heredoc();
		return (-1);
	}
	return (heredoc2);
}
