#include "minishell.h"
#include "execution.h"
#include "parsing.h"

// Sorts an array of strings using bubble sort.
// If strings are out of order (current string is 
// lexicographically greater than the next), it swaps them
void	sort_array(char **arr, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
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

// Duplicates the environment array and returns a sorted copy.
// Counts the number of ENV vars -> Allocates memory for the copy
// create individual string copies -> sort the copied env
// returns the sorted copy
char	**sort_env(char **env)
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

// Prints one environment variable in the format 
// VAR="value" (if value exists) or just VAR.
// Always adds a newline at the end.
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

// Prints all environment variables in sorted order 
// with the prefix "declare -x ".
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

// Executes the export builtin command:
// If no arguments are given, prints the sorted environment.
// Otherwise, validates each argument and updates or adds 
// the environment variable.
int	execute_export(char **env, t_cmd *cmd)
{
	int	i;

	if (!cmd->cmd_arr[1])
	{
		print_sorted_env(env);
		return (0);
	}
	i = 1;
	while (cmd->cmd_arr[i])
	{
		if (!is_valid_identifier(cmd->cmd_arr[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->cmd_arr[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			update_env(&env, cmd->cmd_arr[i]);
		i++;
	}
	return (0);
}
