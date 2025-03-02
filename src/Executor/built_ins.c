#include "../../inc/minishell.h"
#include "execution.h"

// echo w option -n
void execute_echo(char **env, t_cmd *cmd) // TODO: fix: echo (\n not printing)
{
    (void) env;
    int i;
    int newline_check;

    i = 0;
    newline_check = 1;
    // -n check first -> if -n, dont have \n at end 
    if (ft_strcmp(cmd->cmd_arr[1], "-n") == 0)
    {
        newline_check = 0;
        i++;
    }

    while (cmd->cmd_arr[i])
    {
        write(1, cmd->cmd_arr[i], ft_strlen(cmd->cmd_arr[i]));
        if (cmd->cmd_arr[i + 1])
        {
            write(1, " ", 1);
        }
        i++;
    }

    if (newline_check == 1)
    {
        write (1, "\n", 1);
    }
}

int is_built_in(char **env, t_cmd *cmd) // TODO: reduce return (1) to one
{
	(void) env;

	if (ft_strcmp(cmd->cmd_arr[0], "echo") == 0)
    {
        execute_echo(env, cmd);
		return (1);
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd_arr[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd_arr[0], "export") == 0)
    {
        // TODO: J
		return (1);
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd_arr[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd_arr[0], "exit") == 0)
		return (1);
	
	return (0);
}
