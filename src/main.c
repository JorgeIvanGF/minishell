
#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include "../inc/signals.h"

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

// // The Main function __________________________________________________
// int main(int argc, char **argv, char **env)
// {
// 	char *input;
// 	t_minishell *minishell;
// 	t_lst_token	*tokens;

// 	(void) argc;
// 	(void) argv;

// 	init_minishell(&minishell, env);// Initialize outside the while 
// 	g_signum = 0;
// 	setup_signals_interactive(); // SIGNALS: Initial setup
	
// 	while (1)
// 	{
// 		input = readline(ORANGE"MINISHELL> "RESET); // Display prompt and get input
// 		if (!input) // If Ctrl+D is pressed, exit
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		if (*input) // If input is not empty, add it to history
// 			add_history(input);

// 		if (!first_checks(input))
// 		{
// 			free(input);
// 			continue;
// 		}
// 		// Tokenize part___________________________________________________
// 		tokens = tokenize(input); 
// 		if (!tokens)
// 		{
// 			//printf(RED"Error: Tokenization failed.\n"RESET);
// 			free(input);
// 			continue ;
// 		}
// 		print_tokens(tokens); // TO DEBUG
// 		// Syntax part (using tokens list)_______________________________
// 		if (syntax_check(tokens, minishell))
// 		{
// 			free_token_list(tokens);
// 			free(input);
// 			continue ;
// 		}
// 		// Parsing part__________________________________________________
// 		minishell->list_cmd = parser(tokens, minishell);
// 		if (!minishell->list_cmd)
// 		{
// 			printf(RED"Failed to Parse the tokens\n"RESET);
// 			free_token_list(tokens);
// 			free(input);
// 			exit_shell(minishell);
// 		}
// 		print_command_list(minishell->list_cmd); // TO DEBUG
// 		ft_execution(minishell); // To Paula
// 		continue_shell(minishell, &tokens, &input);
// 	}
// 	exit_shell(minishell);
// 	return (0); // paula con el resultado de ft_execution;

// }


// Disables the terminal's echoing of control characters.
// This function retrieves the current terminal settings, 
// clears the ECHOCTL flag (which normally causes control 
// characters like Ctrl-C to be displayed as "^C"),
// and applies the updated settings immediately.
void disable_echoctl(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Process the command loop
void command_loop(t_minishell *minishell)
{
	char *input;
	t_lst_token *tokens;
	
	while (1) // changed by Paula
	{
		input = get_and_validate_input();
		if (input == NULL)
		{
			if (handle_null_input())
				break;
			continue;
		}
		if (handle_empty_input(input))
			continue;
		// if (handle_only_spaces(input)) // TODO: error" "
		// {
		// 	//free(input);
		// 	continue;
		// }
		if (tokenize_input(input, &tokens))
			continue;
		if (process_inputs(minishell, tokens, input))
			continue;
	}
}



// The Main function 
// int main(int argc, char **argv, char **env) // Jorge old V
// {
// 	t_minishell *minishell;
	
// 	(void) argc;
// 	(void) argv;
// 	init_minishell(&minishell, env);
// 	disable_echoctl(); // Disable echoing of control characters
// 	setup_signals_interactive();
// 	command_loop(minishell); /
// 	exit_shell(minishell); 
// 	return (0);
// }

int main(int argc, char **argv, char **env) // Paula new V
{
	t_minishell *minishell;
	// int exit_code;
	
	(void) argc;
	(void) argv;
	init_minishell(&minishell, env);
	disable_echoctl(); // Disable echoing of control characters
	// setup_signals_interactive();

	command_loop(minishell); // parsing, execution happens here
	// printf("exit flag in main = %d\n", minishell->exit_requested); // for testing

	exit_shell(minishell); 
	// printf("final exit code (in main) = %d\n", exit_code); // for testing

	return (0);
}