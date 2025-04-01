/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:52:19 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:52:20 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// Simple initialization of the tokens list
void	init_tokens(t_lst_token *tokens)
{
	tokens->head = NULL;
	tokens->tail = NULL;
	tokens->size = 0;
}

// Handles token creation and addition to the list
int	add_token_to_list(char *word, t_lst_token *tokens)
{
	t_token	*token;

	token = new_token(word, get_token_type(word));
	if (!token)
		return (0);
	if (!tokens->head)
		tokens->head = token;
	else
		tokens->tail->next = token;
	tokens->tail = token;
	tokens->size++;
	return (1);
}

// Main lexer function:
// skip initial spaces->pass tru input->if finds operator->process it
// else process standart token
int	ft_lexer(char *input, t_lst_token *tokens)
{
	int	i;

	if (!input || !tokens)
		return (0);
	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	while (input[i])
	{
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (!process_operator(input, &i, tokens))
				return (0);
		}
		else
		{
			if (!process_standard_token(input, &i, tokens))
				return (0);
		}
	}
	return (1);
}

// Creation of the list of tokens, initialize it, 
// lexer the input into tokens  
t_lst_token	*tokenize(char *input)
{
	t_lst_token	*tokens;

	tokens = malloc(sizeof(t_lst_token));
	if (!tokens)
		return (NULL);
	init_tokens(tokens);
	if (!ft_lexer(input, tokens))
	{
		free_token_list(tokens);
		return (NULL);
	}
	return (tokens);
}
