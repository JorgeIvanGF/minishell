#include "minishell.h"
#include "execution.h"
#include "parsing.h"

// Checks if the given string is a valid identifier for an ENV var
// A valid identifier must start with a letter or underscore and 
// contain only alphanumeric or underscore characters before any '='.
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// Appends a new variable to the environment array when 
// it is not already present.
void	append_new_var(char ***env, const char *var, int count)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return ;
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[count] = ft_strdup(var);
	new_env[count + 1] = NULL;
	free(*env);
	*env = new_env;
}

// Updates an existing ENV var if it exists, or adds it if not.
// It compares the variable name up to the '=' character.
void	update_env(char ***env, const char *var)
{
	int	i;
	int	var_len;

	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], var, var_len) && (*env)[i][var_len] == '=') // TODO: segfault
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(var);
			return ;
		}
		i++;
	}
	append_new_var(env, var, i);
}
