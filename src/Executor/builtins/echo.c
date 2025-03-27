#include "execution.h"
#include "minishell.h"
#include "parsing.h"

// echo w option -n
// TODO: add function description (// -n check first -> if -n, dont have \n at end)
void	execute_echo(t_cmd *cmd)
{
	int	i;
	int	newline_check;

	i = 1;
	newline_check = 1;
	if (cmd->cmd_arr[1] != NULL && ft_strcmp(cmd->cmd_arr[1], "-n") == 0)
	{
		newline_check = 0;
		i++;
	}
	while (cmd->cmd_arr[i])
	{
		write(1, cmd->cmd_arr[i], ft_strlen(cmd->cmd_arr[i]));
		if (cmd->cmd_arr[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline_check == 1)
		write(1, "\n", 1);
}
