#include "execution.h"
#include "minishell.h"
#include "parsing.h"

// pwd with no options
int	execute_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (0);
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	return (1);
}
