#include "../../inc/minishell.h"
#include "execution.h"

void	execution(char **env, t_cmd *cmd) 
{
	char	*path;
	char	**path_cmds;
	char	*found_path;

	path = get_path(env);
	path_cmds = get_paths_cmds(path);
	found_path = find_path(path_cmds, cmd->cmd_arr[0]);
	if (execute(found_path, cmd, env) == -1)
	{
		ft_free_2d(path_cmds);
		free(found_path);
		write(2, "minishell: command not found: ", 26);
		write(2, cmd->cmd_arr[0], ft_strlen(cmd->cmd_arr[0]));
		write(2, "\n", 1);
		exit(127);
	}
}

int	execute_cmd(t_cmd *cmd, char **env) // do not touch // TODO: almost finished, pipe-check
{
	int	id;
	int fd[2];

	pipe(fd);
	id = fork();
	if (id == 0) 
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (redirecting_stdin(cmd) == 1 && redirecting_stdout(cmd) == 1) // TODO: recheck where to call (what if no file found?)
		{
			execution(env, cmd);
		}
		exit(0); // TODO: line needs to be double checked bc of #
	}
	else 
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return(id);
}

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

void looping_through_list_commands(t_lst_cmd *list_cmds, char **env)
{
	t_cmd *current;
	int status;
	int id;

	current = list_cmds->head;
	while(current != NULL)
	{ 
		id = execute_cmd(current, env); // alle fd redirection redirecten stdin, stdout
		current = current->next;
	}
		waitpid(id,&status, 0);
		while (waitpid(-1, NULL, WNOHANG) != -1) //WUNTRACED
			;
}

// go thru entire cmd list. if command found, execute w above function, if not, execution will handle
void checking_list_cmds_for_exec(t_lst_cmd *list_cmds, char **env)
{
	t_cmd *current;
	int cmd_list_position;

	cmd_list_position = 1;
	current = list_cmds->head;
	while(current != NULL)
	{
		printf("%d. COMMAND\n", cmd_list_position);
		execute_cmd(current, env);
		current = current->next;
		cmd_list_position++;
	}
}

void ft_execution (t_minishell *minishell)
{
	(void) minishell;
	t_lst_cmd *list_cmds;
	t_cmd *first_cmd;
	t_cmd *second_cmd;
	t_cmd *third_cmd;
	char **cmd_arr0;
	char **cmd_arr1;
	char **cmd_arr2;
	t_lst_rdir *list_rdir1;
	t_lst_rdir *list_rdir2;
	t_lst_rdir *list_rdir3;
	t_rdir *first_rdir1;
	t_rdir *second_rdir1;
	t_rdir *three_rdir1;
	t_rdir *four_rdir1;
	t_rdir *five_rdir1;
	t_rdir *first_rdir2;
	t_rdir *second_rdir2;
	t_rdir *first_rdir3;
	t_rdir *second_rdir3;
	t_rdir *three_rdir3;

	// printf("here00\n");
	// initialize first command (head) ex.: "ls -a <out"
	cmd_arr0 = init_cmd_array("ls -a");
	cmd_arr1 = init_cmd_array("ls -a");
	cmd_arr2 = init_cmd_array("ls -a");
	// print_cmd_array(cmd_arr0);
	// print_cmd_array(cmd_arr1);
	// print_cmd_array(cmd_arr2);

	// FIRST COMMAND
	first_rdir1 = init_redirection(RD_IN, "infile1");
	// print_redirection(first_rdir);

	second_rdir1 = init_redirection(RD_IN, "out");
	first_rdir1->next = second_rdir1;

	three_rdir1 = init_redirection(RD_APND, "apnd");
	second_rdir1->next = three_rdir1;

	four_rdir1 = init_redirection(RD_IN, "infile2");
	three_rdir1->next = four_rdir1;

	five_rdir1 = init_redirection(RD_IN, "infile3");
	four_rdir1->next = five_rdir1;

	list_rdir1 = init_list_redirection(first_rdir1, five_rdir1, 5);
	// print_list_redirection(list_rdir);/

	first_cmd = init_command(cmd_arr0, list_rdir1);
	// print_command(first_cmd);


	// SECOND COMMAND
	first_rdir2 = init_redirection(RD_IN, "infile2");

	second_rdir2 = init_redirection(RD_OUT, "xxx");
	first_rdir2->next = second_rdir2;

	list_rdir2 = init_list_redirection(first_rdir2, second_rdir2, 2);

	second_cmd = init_command(cmd_arr1, list_rdir2);
	first_cmd->next = second_cmd;


	// THIRD COMMAND
	first_rdir3 = init_redirection(RD_IN, "out");

	second_rdir3 = init_redirection(RD_IN, "infile1");
	first_rdir3->next = second_rdir3;

	three_rdir3 = init_redirection(RD_IN, "infile3");
	second_rdir3->next = three_rdir3;
	// print_command(second_cmd);

	list_rdir3 = init_list_redirection(first_rdir3, three_rdir3, 3);

	third_cmd = init_command(cmd_arr2, list_rdir3);
	second_cmd->next = third_cmd;
	// print_command(third_cmd);


	list_cmds = init_list_commands(1, first_cmd, NULL); 
	print_list_commands(list_cmds);

//88888888888888888888888888888888888888888888888888888888888888888888 exec
	// saving original of stdin & stdout
	int copy_of_stdin_fd = dup(STDIN_FILENO);
	int copy_of_stdout_fd = dup(STDOUT_FILENO);
	looping_through_list_commands(list_cmds, minishell->env); // going through list_cmds & checking for RD_IN & file
	// stdin & stdout has to be set back to its original (create ft for it later)
	dup2(copy_of_stdin_fd, STDIN_FILENO);
	close(copy_of_stdin_fd);
	dup2(copy_of_stdout_fd, STDOUT_FILENO);
	close(copy_of_stdout_fd);


	// may be deleted: checking_list_cmds_for_exec(list_cmds, minishell->env); // goes thru cmd list and executes all cmds


 



	// t_redirection *redirection_0;
	// t_redirection *redirection_1;
	// t_redirection *redirection_2;
	// t_redirection *redirection_3;
	// t_list_redirection *list_redirection;
	
	// redirection_0 = init_redirection(0, NULL);
	// // printf("redirection 0: type = %d, name = %s\n", redirection_0->type, redirection_0->name);
	// redirection_1 = init_redirection(1, NULL);
	// // printf("redirection 1: type = %d, name = %s\n", redirection_1->type, redirection_1->name);
	// redirection_2 = init_redirection(2, NULL);
	// // printf("redirection 2: type = %d, name = %s\n", redirection_2->type, redirection_2->name);
	// redirection_3 = init_redirection(3, NULL);
	// // printf("redirection 3: type = %d, name = %s\n", redirection_3->type, redirection_3->name);
	
	// redirection_0->next = redirection_1;
	// redirection_1->next = redirection_2;
	// redirection_2->next = redirection_3;
	// redirection_3->next = NULL;

	// list_redirection = init_list_redirection(redirection_0, redirection_3, 4);
}
