#include "minishell.h"
#include "parsing.h"

// Handle NULL input (Ctrl+D case):
// Signal to break the main loop
int	handle_null_input(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		return (1);
	return (0);
}
