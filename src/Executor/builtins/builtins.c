#include "execution.h"
#include "minishell.h"
#include "parsing.h"

// executes corresponding builtins
int	execute_builtin(t_cmd *cmd, t_minishell *minishell)
{
	if (!(cmd && cmd->cmd_arr && cmd->cmd_arr[0]))
		return (0);
	if (ft_strcmp(cmd->cmd_arr[0], "echo") == 0 || ft_strcmp(cmd->cmd_arr[0],
			"/bin/echo") == 0)
		return (execute_echo(cmd));
	else if (ft_strcmp(cmd->cmd_arr[0], "cd") == 0 || ft_strcmp(cmd->cmd_arr[0],
			"/usr/bin/cd") == 0)
		return (execute_cd(cmd));
	else if (ft_strcmp(cmd->cmd_arr[0], "pwd") == 0
		|| ft_strcmp(cmd->cmd_arr[0], "/bin/pwd") == 0)
		return (execute_pwd());
	else if (ft_strcmp(cmd->cmd_arr[0], "export") == 0)
		return (execute_export(&minishell->env, cmd));
	else if (ft_strcmp(cmd->cmd_arr[0], "unset") == 0)
		return (execute_unset(minishell->env, cmd));
	else if (ft_strcmp(cmd->cmd_arr[0], "env") == 0
		|| ft_strcmp(cmd->cmd_arr[0], "/usr/bin/env") == 0
		|| ft_strcmp(cmd->cmd_arr[0], "ENV") == 0)
		return (execute_env(minishell->env, cmd));
	else if (ft_strcmp(cmd->cmd_arr[0], "exit") == 0)
		return (execute_exit(cmd, minishell));

	return (0);
}

// checks if a builtin
int	is_builtin(t_cmd *cmd)
{
	if (!(cmd && cmd->cmd_arr && cmd->cmd_arr[0]))
		return (0);
	if ((ft_strcmp(cmd->cmd_arr[0], "echo") == 0) || (ft_strcmp(cmd->cmd_arr[0],
				"/bin/echo") == 0) || (ft_strcmp(cmd->cmd_arr[0], "cd") == 0)
		|| (ft_strcmp(cmd->cmd_arr[0], "/usr/bin/cd") == 0)
		|| (ft_strcmp(cmd->cmd_arr[0], "pwd") == 0)
		|| (ft_strcmp(cmd->cmd_arr[0], "/bin/pwd") == 0)
		|| (ft_strcmp(cmd->cmd_arr[0], "export") == 0)
		|| (ft_strcmp(cmd->cmd_arr[0], "unset") == 0)
		|| (ft_strcmp(cmd->cmd_arr[0], "env") == 0)
		|| (ft_strcmp(cmd->cmd_arr[0], "ENV") == 0)
		|| (ft_strcmp(cmd->cmd_arr[0], "/usr/bin/env") == 0)
		|| (ft_strcmp(cmd->cmd_arr[0], "exit") == 0))
	{
		return (1);
	}
	return (0);
}
