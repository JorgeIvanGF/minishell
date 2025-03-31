#include "../../inc/minishell.h"
#include "execution.h"

void	print_redirection(t_rdir *redirection)
{
	printf("---------------------- REDIRECTION ----------------------------\n");
	printf("redirection type = %d\n", redirection->type);
	printf("redirection name = %s\n", redirection->name);
	printf("---------------------------------------------------------------\n");
}

void	print_list_redirection(t_lst_rdir *list_redirection)
{
	t_rdir	*current;

	if (list_redirection)
	{
		current = list_redirection->head;
		printf("********************** LIST REDIRECTION *****************\n");
		while (current != NULL)
		{
			print_redirection(current);
			current = current->next;
		}
		printf("*********************************************************\n");
	}
}

void	print_cmd_array(char **cmd_arr)
{
	int	i;

	printf("********************** COMMAND ARRAY **********************\n");
	i = 0;
	while (cmd_arr && cmd_arr[i] != NULL)
	{
		printf("command array [%d] = %s\n", i, cmd_arr[i]);
		i++;
	}
	printf("***********************************************************\n");
}

void	print_command(t_cmd *cmd)
{
	printf("---------------------- COMMAND ----------------------------\n");
	print_cmd_array(cmd->cmd_arr);
	print_list_redirection(cmd->list_rdir);
	printf("-----------------------------------------------------------\n");
}

void	print_list_commands(t_lst_cmd *list_cmds)
{
	t_cmd	*current;
	int		i;

	current = list_cmds->head;
	printf("********************** LIST COMMANDS ********************\n");
	i = 0;
	while (current != NULL)
	{
		printf("%d. ", i);
		i++;
		print_command(current);
		current = current->next;
	}
	printf("********************************************************\n");
}
