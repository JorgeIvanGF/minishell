#include "execution.h"
#include "minishell.h"
#include "parsing.h"

// pwd with no options
int	execute_pwd(void) // TODO: check return value (0 success, 1 failure) for all built ins if used or not
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	return (0);
}
