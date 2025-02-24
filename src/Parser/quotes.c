
#include "minishell.h"
#include "parsing.h"

void	check_single(char **arr)
{
	char *new;
	char *old;

	if (!arr || !arr[0] || ft_strlen(arr[0]) < 2)
		return ; //to ckeck if its only '\''
	if ((*arr)[0] != '\'' || (*arr)[ft_strlen(*arr) - 1] != '\'')
		return ; //ensure its quoted
	old = *arr;
	new = ft_substr(arr[0], 1, ft_strlen(arr[0]) - 2);
	if (!new)
	{
		printf(RED"Failed malloc for new string\n'"RESET);
		return;
	}
	printf("new = %s\n", new);
	arr[0] = new;
	free(old);
}

void	check_quotes(char **cmd_arr)
{
	int	i;
	
	i = 0;
	while(cmd_arr[i])
	{
		if(cmd_arr[i][0] == '\'' || cmd_arr[i][0] == '"')
		{
			if(cmd_arr[i][0] == '\'')
				check_single(&cmd_arr[i]);
			/* else
				check_double(&cmd_arr[i]); */
		}		
		i++;
	}
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