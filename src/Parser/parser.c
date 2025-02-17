#include "minishell.h"
#include "parsing.h"

void	ft_copy_env(t_minishell *shell, char **env)
{
	
}

void	init_minishell(t_minishell *shell, char **env)
{
	shell->env = NULL;
	ft_copy_env(shell, env);
}
