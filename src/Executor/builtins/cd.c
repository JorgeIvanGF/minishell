#include "minishell.h"
#include "execution.h"
#include "parsing.h"

/*
change directory with only a relative or absolute path
-
*/ 
int execute_cd(t_cmd *cmd)
{  
    char *home_path;
    char *replaced_path;

    if (cmd->cmd_arr[1] == NULL) // replace ~ with HOME path, if ~ found 
    {
        home_path = getenv("HOME");
        if (chdir(home_path) == -1)
            return (perror("cd"), 1);
    }
    else if (cmd->cmd_arr[1] && cmd->cmd_arr[1][0] == '~') // replace ~ with HOME path, if ~ found, and add to rest of path
    {
        home_path = getenv("HOME");
        replaced_path = ft_strjoin(home_path, cmd->cmd_arr[1] +1);
        if (chdir(replaced_path) == -1)
            return (perror("cd"), 1);
        ft_free(replaced_path);
    }
    else if (chdir(cmd->cmd_arr[1]) == -1)
        return (perror("cd"), 1);
    return (0);
}

// go thru string to check for ~., then add home (ex. Users/pauladrettas) to replace
