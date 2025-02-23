#include "../../inc/minishell.h"
#include "execution.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env != NULL && env[i] != NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=')
		{
			return (env[i]);
		}
		i++;
	}
	return (NULL);
}

char	**get_paths_cmds(char *str)
{
	char	**path_cmds;

	path_cmds = ft_split(str + 5, ':');
	return (path_cmds);
}

char	*check_paths_w_cmd(char **path_cmds, char *cmd)
{
	int		i;
	char	*first_part_path;
	char	*total_part_w_cmd;
	char	**splitted_cmd;

	splitted_cmd = ft_split(cmd, ' ');
	i = 0;
	while (path_cmds != NULL && path_cmds[i] != NULL)
	{
		first_part_path = ft_strjoin(path_cmds[i], "/");
		if (!first_part_path)
			return (NULL);
		total_part_w_cmd = ft_strjoin(first_part_path, splitted_cmd[0]);
		if (!total_part_w_cmd)
			return (free(first_part_path), NULL);
		if (access(total_part_w_cmd, X_OK) == 0)
		{
			ft_free_2d(splitted_cmd);
			return (free(first_part_path), total_part_w_cmd);
		}
		free(first_part_path);
		free(total_part_w_cmd);
		i++;
	}
	return (ft_free_2d(splitted_cmd), NULL);
}

char	*find_path(char **path_cmds, char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (cmd);
	else
	{
		return (check_paths_w_cmd(path_cmds, cmd));
	}
}

int	execute(char *found_path, t_cmd *cmd, char **env)
{
	if (execve(found_path, cmd->cmd_arr, env) == -1)
	{
		ft_free_2d(cmd->cmd_arr);
		return (-1);
	}
	return (0);
}
