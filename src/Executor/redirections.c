#include "minishell.h"
#include "execution.h"

int redirect_stdin(t_cmd *cmd);
int redirect_stdout(t_cmd *cmd); 

// Redirect both STDIN and STDOUT based on the redirection types in the command
int redirect_io(t_cmd *cmd)
{
	return (redirect_stdin(cmd) && redirect_stdout(cmd)); // TODO: memorize 
}

// Redirect STDIN from specified file(s) based on the redirection type in the command
int redirect_stdin(t_cmd *cmd)
{
	t_rdir *current;
	int fd_infile;

	fd_infile = 1;
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
					write(2, "minishell: ", 11); // TODO: create error message file.c 
					write(2, current->name, ft_strlen(current->name));
					write(2, ": No such file or directory\n", 28); 
					return (-1);
				}
				dup2(fd_infile, STDIN_FILENO); 
				close(fd_infile);
			}
			current = current->next;
		}
	}
	return (1);
}

// Redirect STDOUT to specified file(s) based on the redirection type in the command
int redirect_stdout(t_cmd *cmd) 
{
	t_rdir *current;
	int fd_outfile;

	fd_outfile = 1;
	if(cmd && cmd->list_rdir && cmd->list_rdir->head)
	{
		current = cmd->list_rdir->head;
		while(current != NULL)
		{
			if (current->type == RD_OUT)
			{
				fd_outfile = open(current->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			else if (current->type == RD_APND)
			{
				fd_outfile = open(current->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}

			if (fd_outfile == -1)
			{
				write(2, "minishell: ", 11);  // TODO: create error message file.c 
				write(2, current->name, ft_strlen(current->name));
				write(2, ": No such file or directory\n", 28);
				return (-1);
			}
			dup2(fd_outfile, STDOUT_FILENO);
			close(fd_outfile);

			current = current->next;
		}
	}
	return (1);
}
