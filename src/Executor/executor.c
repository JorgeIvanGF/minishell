#include "../../inc/minishell.h"

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
	list_cmds->size = size; // 1 
	list_cmds->head = head; // first command
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
	t_lst_rdir *list_rdir;
	t_rdir *first_rdir;
	t_rdir *second_rdir;
	t_rdir *three_rdir;
	t_rdir *four_rdir;

	// initialize first command (head) ex.: "ls -a <out"
	cmd_arr0 = init_cmd_array("ls -a");
	cmd_arr1 = init_cmd_array("wc -l");
	cmd_arr2 = init_cmd_array("ls");
	// print_cmd_array(cmd_arr);


	first_rdir = init_redirection(RD_OUT, "out");
	// print_redirection(first_rdir);

	second_rdir = init_redirection(RD_IN, "infile1");
	first_rdir->next = second_rdir;

	three_rdir = init_redirection(RD_APND, "apnd");
	second_rdir->next = three_rdir;

	four_rdir = init_redirection(RD_IN, "nmsdc");
	three_rdir->next = four_rdir;

	list_rdir = init_list_redirection(first_rdir, three_rdir, 3);
	// print_list_redirection(list_rdir);/


	first_cmd = init_command(cmd_arr0, list_rdir);
	// print_command(first_cmd);
	
	second_cmd = init_command(cmd_arr1, list_rdir);
	first_cmd->next = second_cmd;
	// print_command(second_cmd);

	third_cmd = init_command(cmd_arr2, list_rdir);
	second_cmd->next = third_cmd;
	// print_command(third_cmd);

	list_cmds = init_list_commands(1, first_cmd, NULL); 
	print_list_commands(list_cmds);




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
