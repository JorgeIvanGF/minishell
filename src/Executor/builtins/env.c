#include "execution.h"
#include "minishell.h"
#include "parsing.h"

// env with no options or arguments
int	execute_env(char **env, t_cmd *cmd)
{
	int		i;
	char	**check_export;

	if (get_path(env) == NULL)
	{
		error_no_file_directory("env");
		return (0);
	}
	if (env && cmd->cmd_arr[1])
	{
		error_env_no_file_directory(cmd->cmd_arr[1]);
		return (0);
	}
	i = 0;
	while (env && env[i] != NULL)
	{
		check_export = ft_split(env[i], '=');
		if (check_export[1])
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
		i++;
		ft_free_2d(check_export);
	}
	return (1);
}
