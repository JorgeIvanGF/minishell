
#include "../inc/minishell.h"
#include "../inc/parsing.h"

void *init_minishell (t_minishell **minishell,char **env)
{
	//t_minishell *minishell;
	
	*minishell = malloc(1 * (sizeof(t_minishell)));
	
	(*minishell)->env = env;
	(*minishell)->list_cmd = NULL;

	return(minishell);
}

/*
// PAULA MAIN ..............................................................

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
// ..............................................................................
*/



// JORGE MAIN ------------------------------------------------------------------


// To Test the Lexer (Tmporary function)
void print_tokens(t_lst_token *tokens)
{
	t_token *curr = tokens->head;
	while (curr)
	{
		printf("Token: %-10s | Type: %d\n", curr->value, curr->type);
		curr = curr->next;
	}
}


int main(int argc, char **argv, char **env)
{
	char *input;
	t_minishell *minishell;
	t_lst_token	*tokens;

	(void) argc;
	(void) argv;
	(void) env;

	//minishell = malloc((sizeof(t_minishell *)));
	while (1)
	{
		init_minishell(&minishell, env);
		input = readline(ORANGE"MINISHELL> "RESET); // Display prompt and get input
		if (!input) // If Ctrl+D is pressed, exit
		{
			printf("exit\n");
			break;
		}
		if (*input) // If input is not empty, add it to history
			add_history(input);
		printf("--readline: %s\n", input); // to test the readline

		// Tokenize part
		tokens = tokenize(input); 
		if (!tokens)
		{
			printf(RED"Error: Tokenization failed.\n"RESET);
			free(input);
			continue ;
		}

		print_tokens(tokens); // Debugging tokens

		// Check syntax part: using tokens list
		if (syntax_check(tokens))
		{
			free_token_list(tokens);
			free(input);
			continue ;
		}

		// Parsing part
		parser(tokens, minishell);
		free_token_list(tokens);
		free(input);
		
		/*
		
		//........... Execution Part......................
		ft_execution(minishell); // To Paula

	
		
		// ............Free Everything....................
		free(input); // Free memory allocated by readline

		*/
	}
	return 0;
}