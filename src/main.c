
#include "../inc/minishell.h"
#include "../inc/parsing.h"


// JORGE MAIN ------------------------------------------------------------------


// To Test the Lexer (Tmporary function)
void print_tokens(t_lst_token *tokens)
{
	t_token *curr = tokens->head;
	printf(YELLOW"TOKEN VALUES AND TYPES\n"RESET);
	while (curr)
	{
		printf("Token: %-10s | Type: %d\n", curr->value, curr->type);
		curr = curr->next;
	}
}
// To Test the copy of ENV (Tmporary function)
void	ft_print_env(t_minishell *minishell)
{
	char **arr;

	arr = minishell->env;
	int i = 0;
	while (arr[i])
	{
		printf("\nEnv[%d]= %s\n", i, arr[i]);
		i++;
	}
}


int main(int argc, char **argv, char **env)
{
	char *input;
	t_minishell *minishell;
	t_lst_token	*tokens;

	(void) argc;
	(void) argv;

	init_minishell(&minishell, env);// Initialize outside the while 

	while (1)
	{
		input = readline(ORANGE"MINISHELL> "RESET); // Display prompt and get input
		if (!input) // If Ctrl+D is pressed, exit
		{
			printf("exit\n");
			break;
		}
		if (*input) // If input is not empty, add it to history
			add_history(input);

		if (!first_checks(input))
			continue;
		
		// Tokenize part___________________________________________________
		tokens = tokenize(input); 
		if (!tokens)
		{
			//printf(RED"Error: Tokenization failed.\n"RESET);
			free(input);
			continue ;
		}

		print_tokens(tokens); // TO DEBUG

		// Syntax part (using tokens list)_______________________________
		if (syntax_check(tokens, minishell))
		{
			free_token_list(tokens);
			free(input);
			continue ;
		}

		
		// Parsing part__________________________________________________
		minishell->list_cmd = parser(tokens, minishell);
		if (!minishell->list_cmd)
		{
			printf(RED"Failed to Parse the tokens\n"RESET);
			free_token_list(tokens);
			free(input);
			exit_shell(minishell);
		}

		// int i = 0;
		// while(minishell->env[i])
		// {
		// 	printf("env[%d] = %s\n", i, minishell->env[i]);
		// 	i++;
		// }
		// print_command_list(minishell->list_cmd); // TO DEBUG
		ft_execution(minishell); // To Paula

		
		continue_shell(minishell, &tokens, &input);
		
		
		
		//........... Execution Part......................

	
		
		// ............Free Everything....................
		// free(input); // Free memory allocated by readline

		
	}
	exit_shell(minishell);
	return (0); // paula con el resultado de ft_execution;

}
