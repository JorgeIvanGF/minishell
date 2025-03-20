#include "minishell.h"
#include "parsing.h"

// Process the tokens and execute commands if valid:
// Syntax part (using tokens list)
// Parsing part
int	process_inputs(t_minishell *minishell, t_lst_token *tokens, char *input)
{
	if (syntax_check(tokens, minishell))
	{
		free_token_list(tokens);
		free(input);
		return (1);
	}
	minishell->list_cmd = parser(tokens, minishell);
	if (!minishell->list_cmd)
	{
		printf(RED"Failed to Parse the tokens\n"RESET);
		free_token_list(tokens);
		free(input);
		exit_shell(minishell);
	}
	print_command_list(minishell->list_cmd); // TO DEBUG
	ft_execution(minishell); // To Paula
	continue_shell(minishell, &tokens, &input);
	return (0);
}

// Tokenize the input and handle errors
int	tokenize_input(char *input, t_lst_token **tokens)
{
	*tokens = tokenize(input);
	if (!*tokens)
	{
		//printf(RED"Error: Tokenization failed.\n"RESET);
		free(input);
		return (1);
	}
	print_tokens(*tokens); // TO DEBUG
	return (0);
}

// Handle empty input case
int handle_empty_input(char *input)
{
	if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	return (0);
}

// Check if input consists of only spaces
int handle_only_spaces(char *input)
{
	while (*input)
	{
		if (*input != ' ' && *input != '\t')
			return (0);
		input++;
	}	
	return (1);
}

// Check if input consists of only spaces
// int handle_only_spaces(char *input) // TODO: error
// {
// 	char *temp;
	
// 	temp = input;
// 	while (*input)
// 	{
// 		while (*input == ' ' || *input == '\t')
// 			input++;
// 		if (*input == '\0')
// 		{
// 			input = temp;
// 			free(input);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }


// Handle input readline and validation
char *get_and_validate_input(void)
{
	char *input;
	
	input = readline(ORANGE"MINISHELL> "RESET);
	if (!input) // If Ctrl+D is pressed, exit
	{
		printf("exit\n");
		return (NULL);
	}	
	if (*input) // If input is not empty, add it to history
		add_history(input);
	// if (*input && !first_checks(input))// Only check non-empty inputs
	// {
	// 	printf("is Null...");
	// 	free(input);
	// 	return (NULL);
	// }
	return (input);
}

// Handle NULL input (Ctrl+D case)
int handle_null_input(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		return (1); // Signal to break the main loop
	return (0);
}
