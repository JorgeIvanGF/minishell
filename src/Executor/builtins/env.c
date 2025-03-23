#include "minishell.h"
#include "execution.h"
#include "parsing.h"

// env with no options or arguments  
int execute_env(char **env, t_cmd *cmd)
{
    int i;

    if (env && cmd->cmd_arr[1])
    {
        write(2, "env: ", 5);
        write (2, cmd->cmd_arr[1], ft_strlen(cmd->cmd_arr[1]));
        write (2, ": No such file or directory\n", 28);
        return (1);
    }
    
    i = 0;
    while (env[i] != NULL)
    {
        write(1, env[i], ft_strlen(env[i]));
        write(1, "\n", 1);
        i++;
    }

    return (0);
}
