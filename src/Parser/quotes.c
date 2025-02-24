
#include "minishell.h"
#include "parsing.h"

	void	check_single(char *arr, int i)
	{

	}

void	check_quotes(char **cmd_arr)
{
	int	i;
	char *new;

	i = 0;
	while(cmd_arr[i])
	{
		if(cmd_arr[i][0] == '\'')
		{
			//check_single(cmd_arr[i], i);
			new = malloc(sizeof(char) * (ft_strlen(cmd_arr[i]) - 1));
			if (!new)
			{
				printf(RED"Failed malloc for new string\n'"RESET);
				return;
			}
			new = ft_substr(cmd_arr[i], 1, ft_strlen(cmd_arr[i]) - 2);
			new[ft_strlen(cmd_arr[i]) - 1] = '\0';
			printf("new = %s\n", new);
			cmd_arr[i] = new;
		}
		
		i++;
	}
	//printf("number of cmds = %d\n", i);
}


void	clean_quotes(t_lst_cmd *cmd_list)
{
	t_cmd *curr;
	char **cmd_arr;

	if (!cmd_list)
		{
			printf(RED"Command list empty\n"RESET);
			return ;
		}
	curr = cmd_list->head;
	while(curr)
	{
		cmd_arr = curr->cmd_arr;
		check_quotes(cmd_arr);
		curr = curr->next;
	}
}