#include "execution.h"
#include "minishell.h"
#include "parsing.h"

void	delete_path_from_env(char ***ptr_to_env, int path_line);

// unset with no options
// if matching path in env is found, path will be deleted
int	execute_unset(char **env, t_cmd *cmd)
{
	int		i;
	int		path_line;
	char	**split_env_path;

	i = 1;
	while (cmd && cmd->cmd_arr && cmd->cmd_arr[i])
	{
		path_line = 0;
		while (env[path_line] != NULL)
		{
			split_env_path = ft_split(env[path_line], '=');
			if (!split_env_path)
				return (0);
			if ((ft_strcmp(split_env_path[0], cmd->cmd_arr[i]) == 0))
			{
				ft_free_2d(split_env_path);
				delete_path_from_env(&env, path_line);
				break ;
			}
			ft_free_2d(split_env_path);
			path_line++;
		}
		i++;
	}
	return (1);
}

void	delete_path_from_env(char ***ptr_to_env, int path_line)
{
	char	**env;

	env = *ptr_to_env;
	while (1)
	{
		free(env[path_line]);
		if (env[path_line + 1] == NULL)
		{
			env[path_line] = NULL;
			break ;
		}
		env[path_line] = ft_strdup(env[path_line + 1]);
		path_line++;
	}
}
