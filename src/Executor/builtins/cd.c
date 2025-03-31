#include "execution.h"
#include "minishell.h"
#include "parsing.h"

// change directory with only a relative or absolute path
// '~' is replaced by HOME path
int	execute_cd(t_cmd *cmd)
{
	char	*home_path;
	char	*replaced_path;

	if (cmd->cmd_arr[1] == NULL)
	{
		home_path = getenv("HOME");
		if (chdir(home_path) == -1)
			return (perror("cd"), 0);
	}
	else if (cmd->cmd_arr[1] && cmd->cmd_arr[1][0] == '~')
	{
		home_path = getenv("HOME");
		replaced_path = ft_strjoin(home_path, cmd->cmd_arr[1] + 1);
		if (chdir(replaced_path) == -1)
			return (perror("cd"), 0);
		ft_free(replaced_path);
	}
	else if (chdir(cmd->cmd_arr[1]) == -1)
		return (perror("cd"), 0);
	return (1);
}
