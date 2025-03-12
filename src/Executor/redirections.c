#include "../../inc/minishell.h"
#include "execution.h"

int redirecting_stdout(t_cmd *cmd) // redirect output (out & apnd)
{
	t_rdir *current;
	int fd_outfile;

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
				write(2, "minishell: ", 11); // bash
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

int redirecting_stdin(t_cmd *cmd) // redirect input (in)
{
	t_rdir *current;
	int fd_infile;

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
					write(2, "minishell: ", 11); // bash
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

int redirecting_io(t_cmd *cmd)
{
	return (redirecting_stdin(cmd) && redirecting_stdout(cmd)); // TODO: memorize 
}