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
        perror("pwd"); //==>" : file not found"
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
    
    // if (cmd->cmd_arr[1] == NULL || cmd->cmd_arr[1][0] == '~') // TODO: nur mit m
    // {
        //     if (getenv("HOME") == NULL) // not meeee (but learn how to call this variable)
        //     {
            //         perror ("cd error");
            //         return (1);
            //     }
            // }
            
            if (chdir(cmd->cmd_arr[1]) == -1)
            {
                perror("cd");
                return (1);
            }
            execute_pwd(); // TODO: delete later (only for printing purposes)
            
            return (0);
        }

// env with no options or arguments  
int execute_env(char **env, t_cmd *cmd)
{
    int i;

    if (env && cmd->cmd_arr[1]) // more than one cmd: ".. : No such file or directory"
    {
        write(2, "env: ", 5);
        write (2, cmd->cmd_arr[1], ft_strlen(cmd->cmd_arr[1]));
        write (2, ": No such file or directory\n", 28);
        // perror("env"); // only meant for certain functions
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

// unset with no options
// purpose: it removes one or more variables or functions from the shell environment (if multiple names are provided, it removes each one)
// test: unset PATH (check w "echo $PATH" [output empty line], or "ls" [output ls: No such file or directory], or "env" [same output as ls])

void delete_path_from_env(char **env, char *matching_path, int line)
{
    // use ft_free to delete string path (will be set to NULL, but only matters for last string)
    // copy string from next row into the deleted one
    while (env[line] != NULL)
    {
        ft_free(matching_path);
        env[line] = env[line + 1]; // FIX: strdup
        line++;
    }
}

int execute_unset(char **env, t_cmd *cmd)
{
    int i;
    int j;
    char **split_env_path;


    i = 1;
    while (cmd->cmd_arr && cmd->cmd_arr[i] != NULL)
    {
        j = 0;
        while (env[j] != NULL)
        {
            split_env_path = ft_split(env[j], '=');
            if ((ft_strcmp(split_env_path[0], cmd->cmd_arr[i]) == 0))
            {
                delete_path_from_env(env, env[j], j); //pointer in front of env[j] bc dont want to only modify copy in ft but original
            }
            ft_free_2d(split_env_path);
            j++;
        }
        i++;
    }

    // after array is found, move up the other arrays in env (so there is no space)

    return (0);
}
// unset test example: "unset USER" (USER path should disappear and everything moved up, when entering "env")

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
        // execute_unset(env, cmd);
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "env") == 0)
    {
        execute_env(env, cmd);
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
