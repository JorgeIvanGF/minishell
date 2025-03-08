#include "../../inc/minishell.h"
#include "execution.h"

// echo w option -n
void execute_echo(char **env, t_cmd *cmd)
{
    (void) env;
    int i;
    int newline_check;

    i = 1;
    newline_check = 1;
    // -n check first -> if -n, dont have \n at end 
    if (cmd->cmd_arr[1] != NULL && ft_strcmp(cmd->cmd_arr[1], "-n") == 0)
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

// EXIT STATUS
// The pwd utility exits 0 on success, and >0 if an error occurs.

// pwd with no options
// purpose/output: prints the current working directory (followed by newline)
// only takes one arugment ("pwd")
int execute_pwd() // TODO: check return value (0 success, 1 failure) for all built ins if used or not
{
    char *cwd;
    cwd = getcwd(NULL, 0); 
    if (!cwd)
    {
        perror("pwd error"); //==>" : file not found"
        return (1);
    }
    write(1, cwd, ft_strlen(cwd));
    write (1, "\n", 1);
    free(cwd);
    return (0);
}

// cd with only a relative or absolute path
int execute_cd(char **env, t_cmd *cmd) // chdir. als input mit ~ testen auch dont forgettt
{
    (void) env; // ?

    // if (cmd->cmd_arr[1] == NULL || cmd->cmd_arr[1][0] == '~') 
    // {
    //     if (getenv("HOME") == NULL) // ??
    //     {
    //         perror ("cd error");
    //         return (1);
    //     }
    // }

    if (chdir(cmd->cmd_arr[1]) == -1)
    {
        perror("cd error");
        return (1);
    }
    execute_pwd(); // TODO: delete later (only for printing purposes)

    return (0);
}

// unset with no options
int execute_unset()
{
    
    // return (1); // error

    return (0); // success
}

int execute_builtin(char **env, t_cmd *cmd) // executes builtin
{
	(void) env;

	if (ft_strcmp(cmd->cmd_arr[0], "echo") == 0)
    {
        execute_echo(env, cmd);
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "cd") == 0)
	{
        execute_cd(env, cmd);
    }	
	else if (ft_strcmp(cmd->cmd_arr[0], "pwd") == 0)
    {
        execute_pwd();
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "export") == 0)
    {
        // TODO: J
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "unset") == 0)
    {
        // execute_unset();
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "env") == 0)
    {
        // execute_env();
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "exit") == 0)
    {
        // execute_exit();
    }
    else
    {
        return (0);
    }
	
	return (1);
}

int is_builtin(char **env, t_cmd *cmd) // checks if a builtin
{
	(void) env;

	if ((ft_strcmp(cmd->cmd_arr[0], "echo") == 0) || 
        (ft_strcmp(cmd->cmd_arr[0], "cd") == 0) || 
        (ft_strcmp(cmd->cmd_arr[0], "pwd") == 0) || 
        (ft_strcmp(cmd->cmd_arr[0], "export") == 0) || 
        (ft_strcmp(cmd->cmd_arr[0], "unset") == 0) || 
        (ft_strcmp(cmd->cmd_arr[0], "env") == 0) || 
        (ft_strcmp(cmd->cmd_arr[0], "exit") == 0))
    {
        return (1);
    }

    return (0);
}
