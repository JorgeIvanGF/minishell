#include "execution.h"
#include "minishell.h"
#include "parsing.h"

// env with no options or arguments
int	execute_env(char **env, t_cmd *cmd)
{
	int	i;

	if (env && cmd->cmd_arr[1])
	{
		error_env_no_file_directory(cmd->cmd_arr[1]);
		return (1);
	}
	i = 0;
	while (env && env[i] != NULL)
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
