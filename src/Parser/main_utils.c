/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:51:35 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 01:25:40 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "signals.h"

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
	ft_execution(minishell);
	continue_shell(minishell, &tokens, &input);
	return (0);
}

// Tokenize the input and handle errors
int	tokenize_input(char *input, t_lst_token **tokens)
{
	*tokens = tokenize(input);
	if (!*tokens)
	{
		free(input);
		return (1);
	}
	if (!check_redirection_syntax(*tokens))
	{
		free_token_list(*tokens);
		free(input);
		return (1);
	}
	return (0);
}

// Handle empty input case
int	handle_empty_input(char *input)
{
	if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	return (0);
}

// Check if input consists of only spaces
int	handle_only_spaces(char *input)
{
	while (*input)
	{
		if (*input != ' ' && *input != '\t')
			return (0);
		input++;
	}
	return (1);
}

// Handle input readline and validation:
// If Ctrl+D is pressed 'exit' is printed
// If input is not empty, add it to history
char	*get_and_validate_input(void)
{
	char	*input;

	input = readline(ORANGE"MINISHELL> "RESET);
	if (!input)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}
