#include "../../inc/minishell.h"
#include "execution.h"

t_lst_rdir *init_list_redirection(t_rdir *head, t_rdir *tail, int size)
{
	t_lst_rdir *list_redirection;
	
	list_redirection = malloc(1 * sizeof(t_lst_rdir));
	if (!list_redirection)
	{
		return (NULL);
	}
	list_redirection->head = head;
	list_redirection->tail = tail;
	list_redirection->size = size;

	return(list_redirection);
}

t_rdir *init_redirection(int type, char *name)
{
	t_rdir *redirection; // objekt bzw. instance

	redirection = malloc(1 * sizeof (t_rdir));
	if (!redirection)
	{
		return(NULL);
	}
	redirection->type = type;
	redirection->name = name;
	redirection->next = NULL;

	return(redirection);
}

void print_redirection(t_rdir *redirection)
{
	printf("---------------------- REDIRECTION -------------------------------\n");
	printf("redirection type = %d\n", redirection->type);
	printf("redirection name = %s\n", redirection->name);
	printf("------------------------------------------------------------------\n");
}

void print_list_redirection(t_lst_rdir *list_redirection)
{
	t_rdir *current;

	current = list_redirection->head;
	printf("********************** LIST REDIRECTION *************************************************************************************************\n");
	while(current != NULL)
	{
		print_redirection(current);
		current = current->next;
	}
	printf("*****************************************************************************************************************************************\n");
}

t_cmd *init_command(char **cmd_arr, t_lst_rdir *list_rdir)
{
	t_cmd *cmd;

	cmd = malloc(1 * sizeof(t_cmd));
	if (!cmd)
	{
		return (NULL);
	}
	cmd->cmd_arr = cmd_arr; 
	cmd->list_rdir = list_rdir;
	cmd->next = NULL;
	return(cmd);
}

t_lst_cmd *init_list_commands(int size, t_cmd *head, t_cmd *tail)
{
	t_lst_cmd *list_cmds;

	list_cmds = malloc(1 * sizeof(list_cmds));
	if (!list_cmds)
	{
		return (NULL);
	}
	list_cmds->size = size;
	list_cmds->head = head;
	list_cmds->tail = tail;

	return (list_cmds);
}

void print_cmd_array(char **cmd_arr)
{
	int i;

	printf("********************** COMMAND ARRAY *******************************\n");
	i = 0;
	while(cmd_arr[i] != NULL)
	{
		printf("command %d = %s\n", i, cmd_arr[i]);
		i++;
	}
	printf("******************************************************************\n");
}

void print_command(t_cmd *cmd)
{
	printf("---------------------- COMMAND --------------------------------\n");
	print_cmd_array(cmd->cmd_arr);
	print_list_redirection(cmd->list_rdir);
	printf("------------------------------------------------------------------\n");
}

void print_list_commands(t_lst_cmd *list_cmds)
{
	t_cmd *current;
	int i;

	current = list_cmds->head;
	printf("********************** LIST COMMANDS *************************************************************************************************\n");
	i = 0;
	while (current != NULL)
	{
		printf("%d. ", i);
		i++;
		print_command(current);
		current = current->next;
	}
	printf("***************************************************************************************************************************************\n");
}

char **init_cmd_array(char *str)
{
	char **cmd_arr;

	cmd_arr = ft_split(str, ' ');

	return(cmd_arr);
}

// ORIGINAL
// check if current command has in one of their redirections, a redirection type of RD_IN and existing file
// void checking_for_rdir_type_RD_IN_plus_file(t_cmd *cmd) 
// {
// 	t_rdir *current;
// 	int fd_infile; 
// 	int rdir_list_position;

// 	rdir_list_position = 1;
// 	current = cmd->list_rdir->head;
// 	while(current != NULL)
// 	{
// 		printf("--------------- %d. redirection ---------------\n", rdir_list_position);
// 		if (current->type == RD_IN)
// 		{
// 			printf("success [one]: redirection type RD_IN found.\n");
// 			fd_infile = open(current->name, O_RDONLY);
// 			if (fd_infile == -1)
// 			{
// 				printf("error: corresponding file cannot be opened.\n");
// 				printf("fd infile = %d\n", fd_infile);
// 			}
// 			else
// 			{
// 				printf("success [two]: corresponding file was opened successfully.\n");
// 				printf("fd infile = %d\n", fd_infile);
// 			}
// 		}
// 		// else 
// 		// {
// 		// 	printf("error: neither redirection type RD_IN, nor file found.\n");
// 		// }
// 		rdir_list_position++;
// 		current = current->next;
// 	}
// }

// void looping_through_list_commands(t_lst_cmd *list_cmds)
// {
// 	t_cmd *current;
// 	int cmd_list_position;

// 	cmd_list_position = 1;
// 	current = list_cmds->head;
// 	while(current != NULL)
// 	{
// 		printf("%d. COMMAND\n", cmd_list_position);
// 		checking_for_rdir_type_RD_IN_plus_file(current);
// 		current = current->next;
// 		cmd_list_position++;
// 	}
// }

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

void	execute_cmd(t_cmd *cmd, char **env) // 
{
	int	id;

	id = fork();
	if (id == 0) 
	{
		// TODO: ft for all redirections (< already done, > & >> missing)
		execution(env, cmd);
	}
}

// COPY
void checking_for_rdir_type_RD_IN_plus_file(t_cmd *cmd, char **env) 
{
	t_rdir *current;
	int fd_infile; 

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
				return;
			}
			close(fd_infile);
		}
		current = current->next;
	}
	execute_cmd(cmd, env);
}

void looping_through_list_commands(t_lst_cmd *list_cmds, char **env)
{
	t_cmd *current;

	current = list_cmds->head;
	while(current != NULL)
	{
		checking_for_rdir_type_RD_IN_plus_file(current, env);
		current = current->next;
	}
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
	looping_through_list_commands(list_cmds, minishell->env); // going through list_cmds & checking for RD_IN & file
	// dup2(7, STDIN_FILENO); // stdin is redirected to fd 7
	// close(7); 

	// checking_list_cmds_for_exec(list_cmds, minishell->env); // goes thru cmd list and executes all cmds


 



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
