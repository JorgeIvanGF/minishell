/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:47:13 by jorgutie          #+#    #+#             */
/*   Updated: 2025/02/17 21:19:35 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// Get the token type (based on the enum)
static t_token_type	get_token_type(char *word)
{
	if (!ft_strcmp(word, "|"))
		return PIPE;
	if (!ft_strcmp(word, "<"))
		return REDIR_IN;
	if (!ft_strcmp(word, ">"))
		return REDIR_OUT;
	if (!ft_strcmp(word, ">>"))
		return APPEND;
	if (!ft_strcmp(word, "<<"))
		return HEREDOC;
	return WORD;
}

// Creation of a token with malloc and assign the type
static t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

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
	t_token *token;

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

// Process the word
int	process_word(char *word, t_lst_token *tokens)
{
	if (!word)
		return (0);
	if (!add_token_to_list(word, tokens))
	{
		free(word);
		return (0);
	}
	free(word);
	return (1);
}

// Skip spaces
void	skip_spaces(const char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

// lexer in action
int	ft_lexer(char *input, t_lst_token *tokens)
{
	int		i;
	char	*word;
	t_token	*token;
	
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i]) 
			break;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>') //Special character
			word = extract_operator(&i, input);
		else
			word = extract_word(&i, input); // Normal command/arg
		if (!word)
			return (NULL);
		token = new_token(word, get_token_type(word)); //Add token
		free(word);
		if (!process_word(word, tokens))
			return (0);
	}
	return (1);
}

// Creation of the list of tokens, initialize it, 
// 
t_lst_token	*tokenize(char *input)
{
	t_lst_token	*tokens;
	
	tokens = malloc(sizeof(t_lst_token));
	if (!tokens)
		return (NULL);
	init_tokens(tokens);
	if (!ft_lexer(input, tokens))
	{
		free_token_list(tokens); // TO DO.....
		return (NULL);
	}	
	return (tokens);
}
