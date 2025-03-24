#include "minishell.h"
#include "execution.h"
#include "parsing.h"


void	sort_array(char **arr, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static char	**sort_env(char **env)
{
	int		count;
	int		i;
	char	**env_copy;

	count = 0;
	while (env[count])
		count++;
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	env_copy[count] = NULL;
	sort_array(env_copy, count);
	return (env_copy);
}

void	print_env_line(char *line)
{
	char	*equal;
	int		key_len;

	equal = ft_strchr(line, '=');
	if (equal)
	{
		key_len = equal - line;
		write(1, line, key_len);
		write(1, "=\"", 2);
		ft_putstr_fd(equal + 1, 1);
		write(1, "\"", 1);
	}
	else
		ft_putstr_fd(line, 1);
	write(1, "\n", 1);
}


void	print_sorted_env(char **env)
{
	int		i;
	char	**env_copy;

	env_copy = sort_env(env);
	if (!env_copy)
		return ;
	i = 0;
	while (env_copy[i])
	{
		write(1, "declare -x ", 11);
		print_env_line(env_copy[i]);
		i++;
	}
	i = 0;
	while (env_copy[i])
	{
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
}



int execute_export(char **env, t_cmd *cmd)
{
	int i;

	if (!cmd->cmd_arr[1])
	{
		print_sorted_env(*env);
		return (0);
	}


	return (0);
}