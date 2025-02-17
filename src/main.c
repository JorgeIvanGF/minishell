
#include "../inc/minishell.h"

t_minishell *init_minishell (char **env)
{
	t_minishell *minishell;
	
	minishell = malloc(1 * (sizeof(t_minishell)));
	
	minishell->env = env;
	minishell->list_cmd = NULL;

	return(minishell);
}

int main(int argc, char **argv, char **env)
{
	char *input;
	t_minishell *minishell;
	(void) argc;
	(void) argv;
	(void) env;

	minishell = NULL;
	while (1)
	{
		// init_minishell(minishell, env);
		input = readline(ORANGE"MINISHELL> "RESET); // Display prompt and get input
		if (!input) // If Ctrl+D is pressed, exit
		{
			printf("exit\n");
			break;
		}
		if (*input) // If input is not empty, add it to history
			add_history(input);
		printf("--readline: %s\n", input); // to test the readline
		// if(!syntax_check(input))
			// process_input(input);
		// parser(input, minishell);

		//........... Execution Part......................
		// ft_execution(minishell); // To Paula
		
		// ............Free Everything....................
		free(input); // Free memory allocated by readline
	}
	return 0;
}