#include "minishell.h"
#include "execution.h"
#include "parsing.h"

// TODO: add exit code if builtin fails

// executes corresponding builtins
int	execute_builtin(t_cmd *cmd, t_minishell *minishell)
{
	if (!(cmd && cmd->cmd_arr && cmd->cmd_arr[0]))
		return (0);
	if (ft_strcmp(cmd->cmd_arr[0], "echo") == 0)
		execute_echo(cmd);
	else if (ft_strcmp(cmd->cmd_arr[0], "cd") == 0)
		execute_cd(cmd);
	else if (ft_strcmp(cmd->cmd_arr[0], "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(cmd->cmd_arr[0], "export") == 0)
		execute_export(minishell->env, cmd);
	else if (ft_strcmp(cmd->cmd_arr[0], "unset") == 0)
		execute_unset(minishell->env, cmd);
	else if (ft_strcmp(cmd->cmd_arr[0], "env") == 0)
		execute_env(minishell->env, cmd);
	else if (ft_strcmp(cmd->cmd_arr[0], "exit") == 0)
		execute_exit(cmd, minishell);
	else
		return (0);
	return (1);
}

// checks if a builtin
int	is_builtin(t_cmd *cmd)
{
	if (!(cmd && cmd->cmd_arr && cmd->cmd_arr[0])) // RMB: if one/two/or all of them exist, then move to next if. if all are null, enter.
		return (0);
	if ((ft_strcmp(cmd->cmd_arr[0], "echo") == 0) || 
    (ft_strcmp(cmd->cmd_arr[0], "cd") == 0) || 
    (ft_strcmp(cmd->cmd_arr[0], "pwd") == 0) || 
    (ft_strcmp(cmd->cmd_arr[0], "export") == 0) || 
	(ft_strcmp(cmd->cmd_arr[0], "unset") == 0) || 
	(ft_strcmp(cmd->cmd_arr[0], "env") == 0) || // TODO: also needs to be able to be entered when capitalized (ENV)
	(ft_strcmp(cmd->cmd_arr[0], "exit") == 0))
	{
		return (1);
	}
	return (0);
}
