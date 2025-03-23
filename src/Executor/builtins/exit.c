#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void syntax_check_exit(t_cmd *cmd, t_minishell *minishell); // -1 if fail ; 1 if not
void check_null(t_cmd *cmd, t_minishell *minishell);
void check_empty(t_cmd *cmd, t_minishell *minishell);
void check_non_numeric(t_cmd *cmd, t_minishell *minishell);
void check_too_many_arguments(t_cmd *cmd, t_minishell *minishell);

// TODO: add function description (// formula to calculate exit code if above 255 (module % of 256))
int execute_exit(t_cmd *cmd, t_minishell *minishell)
{
    syntax_check_exit(cmd, minishell);

    minishell->exit_code = ft_atoi(cmd->cmd_arr[1]) % 256; 
    // printf("exit code calculated = %d\n", minishell->exit_code); // just for testing
    printf("exit\n");
    exit_shell(minishell);

    return (1);
}

void syntax_check_exit(t_cmd *cmd, t_minishell *minishell) // -1 if fail ; 1 if not
{
    // case 1 = NULL
    check_null(cmd, minishell);
    // case 2 = ""
    check_empty(cmd, minishell);
    //case 3 = non numeric
    check_non_numeric(cmd, minishell);
    //case 4 = too many arguments
    check_too_many_arguments(cmd, minishell);
} 

void check_null(t_cmd *cmd, t_minishell *minishell)
{
    if(!cmd->cmd_arr[1])
    {
        printf("exit\n");
        minishell->exit_code = 0;
        exit_shell(minishell);
    }
}

void check_empty(t_cmd *cmd, t_minishell *minishell)
{
    if(cmd->cmd_arr[1] && ft_strlen(cmd->cmd_arr[1]) == 0)
    {
        ft_putendl_fd("exit", 2); // TODO: put error messages into own function to call here
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(cmd->cmd_arr[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        minishell->exit_code = 255;
        exit_shell(minishell);
    }
}

void check_non_numeric(t_cmd *cmd, t_minishell *minishell)
{
    int i;

    i = 0;
    if (((cmd->cmd_arr[1] && cmd->cmd_arr[1][i] == '-')
    || (cmd->cmd_arr[1] && cmd->cmd_arr[1][i] == '+')) && cmd->cmd_arr[1][i + 1])
    {
        i++;
    }
    while(cmd->cmd_arr[1] && cmd->cmd_arr[1][i])
    {
        if (!ft_isdigit(cmd->cmd_arr[1][i]))
        {
            ft_putendl_fd("exit", 2); // TODO: put error messages into own function to call here
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(cmd->cmd_arr[1], 2);
            ft_putendl_fd(": numeric argument required", 2);
            minishell->exit_code = 255;
            exit_shell(minishell);
        }
        i++;
    }
}

void check_too_many_arguments(t_cmd *cmd, t_minishell *minishell)
{
    if (cmd->cmd_arr[2])
    {
        ft_putendl_fd("exit", 2); // TODO: put error messages into own function to call here
        ft_putendl_fd("minishell: exit: too many arguments", 2);
        minishell->exit_code = 1;
        exit_shell(minishell);
    }
}
