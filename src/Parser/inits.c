
#include "../inc/minishell.h"
#include "../inc/parsing.h"

// // Check if imput only is ENTER or spaces)
// int	first_checks(char *input)
// {
// 	int	i;

// 	i = 0;
// 	if (input[i] == '\0' || input[i] == ' ')
// 	{
// 		if (input[i] == ' ')
// 		{
// 			while (input[i] == ' ')
// 				i++;
// 			if (input[i] != '\0')
// 				return (1);
// 		}
// 		return (0);
// 	}
// 	return (1);
// }

// Check if imput only is ENTER or spaces)
int	first_checks(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '\0' || input[i] == ' ')
	{
		if (input[i] == ' ')
		{
			while (input[i] == ' ')
				i++;
			if (input[i] == '\0')
				return (0);
		}
		return (0);
	}
	printf("pasa");
	return (1);
}

// To create a Copy of the ENV-VARs
static char	**copy_env(char **env)
{
	int		i;
	int		size;
	char	**copy;

	size = 0;
	while (env[size])
		size++;
	copy = malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// Initialization of minishell and creation of an ENV copy
void	*init_minishell(t_minishell **minishell, char **env)
{
	if (!minishell || !env)
	{
		printf(RED"Nothing to initialize\n"RESET);
		return (NULL);
	}
	*minishell = malloc(1 * (sizeof(t_minishell)));
	if (!(*minishell))
	{
		printf(RED"Failed to allocate minishell\n"RESET);
		return (NULL);
	}
	(*minishell)->env = copy_env(env);
	if (!(*minishell)->env)
	{
		free(minishell);
		(*minishell) = NULL;
		printf(RED"Failed to copy ENV-VAR\n"RESET);
	}
	(*minishell)->list_cmd = NULL;
	(*minishell)->exit_code = 0;
	return (minishell);
}
