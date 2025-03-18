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
void delete_path_from_env(char ***ptr_to_env, int path_line)
{
    char **env;

    env = *ptr_to_env;
    while (1) 
    {
        free(env[path_line]);
        if (env[path_line + 1] == NULL)
        {
            env[path_line] = NULL;
            break;
        }
        env[path_line] = ft_strdup(env[path_line + 1]);
        path_line++;
    }
}

int execute_unset(char **env, t_cmd *cmd)
{
    int i;
    int path_line;
    char **split_env_path;

    i = 1;
    while (cmd && cmd->cmd_arr && cmd->cmd_arr[i])
    {
        path_line = 0;
        while (env[path_line] != NULL)
        {
            split_env_path = ft_split(env[path_line], '=');
            if (!split_env_path)
            {
                return (1);
            }
            if ((ft_strcmp(split_env_path[0], cmd->cmd_arr[i]) == 0))
            {
                ft_free_2d(split_env_path);
                delete_path_from_env(&env, path_line);
                break;
            }
            ft_free_2d(split_env_path);
            path_line++;
        }
        i++;
    }
    return (0);
}

// exit with no options
// echo $? (to see exit code in bash)
// exit code cant go higher than 255. after it starts counting from 0 again (256). formel: % 256
int syntax_check_exit(t_cmd *cmd, t_minishell *minishell) 
{
    int i;
    
    i = 0;
    while (cmd->cmd_arr[1] && cmd->cmd_arr[1][i] != '\0' && cmd->cmd_arr[1][i] == ' ')
    {
        i++;
    }
    if (cmd->cmd_arr[1][i] == '-' || cmd->cmd_arr[1][i] == '+')
    {
        i++;
    } // TODO: fix error: if sign but followed by a space then error w numeric argument (NOT: too many arguments like rn)
    
    while (cmd->cmd_arr[1] && cmd->cmd_arr[1][i] != '\0')
    {
        if (ft_isdigit(cmd->cmd_arr[1][i]) == 0)
        {
            ft_putendl_fd("exit", 2);
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(cmd->cmd_arr[1], 2);
            ft_putendl_fd(": numeric argument required", 2);
            minishell->exit_code = 255;
            return (-1); // undst // in main.c after freeing
        }
        i++;
    }
    return (1);
}

int execute_exit(t_cmd *cmd, t_minishell *minishell)
{
    int entered_exit_code;
    
    if (!cmd->cmd_arr[1]) // if sole input is exit
    {
        write(1, "exit\n", 5);
        minishell->exit_code = 0;
    }
    else if (cmd->cmd_arr[1] && !cmd->cmd_arr[2]) // if input is exit + a number
    {
        if (syntax_check_exit(cmd, minishell) == 1)
        {
            entered_exit_code = ft_atoi(cmd->cmd_arr[1]);
            minishell->exit_code = entered_exit_code % 256; // formula to calculate exit code if above 255 (module % of 256) 
            // printf("exit code calculated = %d\n", minishell->exit_code); // just for testing
        }
    }
    else if (cmd->cmd_arr[2]) // if input is exit but has too many arguments following
    {
        ft_putendl_fd("exit", 2);
        ft_putendl_fd("minishell: exit: too many arguments", 2);
    }

    return (1);
}

int execute_builtin(t_cmd *cmd, t_minishell *minishell) // executes builtin
{
    if (!(cmd && cmd->cmd_arr && cmd->cmd_arr[0]))
    {
        return (0);
    }

	if (ft_strcmp(cmd->cmd_arr[0], "echo") == 0)
    {
        execute_echo(minishell->env, cmd);
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "cd") == 0)
	{
        execute_cd(minishell->env, cmd);
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
        execute_unset(minishell->env, cmd);
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "env") == 0)
    {
        execute_env(minishell->env, cmd);
    }
	else if (ft_strcmp(cmd->cmd_arr[0], "exit") == 0)
    {
        execute_exit(cmd, minishell);
    }
    else
    {
        return (0);
    }
	
	return (1);
}

int is_builtin(t_cmd *cmd) // checks if a builtin
{
    if (!(cmd && cmd->cmd_arr && cmd->cmd_arr[0])) // RMB: if one/two/or all of them exist, then move to next if. if all are null, enter.
    {
        return (0);
    }
    
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
