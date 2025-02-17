/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:47:13 by jorgutie          #+#    #+#             */
/*   Updated: 2025/02/17 20:54:35 by jorgutie         ###   ########.fr       */
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



// Process the word
static int process_word(char *word, t_lst_token *tokens)
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
static void skip_spaces(const char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

// lexer in action
void	ft_lexer(char *input, t_lst_token *tokens)
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
		if (!token)
			return (NULL);
		if (!tokens->head)
			tokens->head = token;
		else
			tokens->tail->next = token;
		tokens->tail = token;
		tokens->size++;
	}
}

// Creation of the list of tokens, initialize it, split the input array by ' '
// tokenize each splitted "word" and at the end free the splits.
t_lst_token *tokenize(char *input)
{
	t_lst_token	*tokens;
	char		**splits;
	int			i;
	
	tokens = malloc(sizeof(t_lst_token));
	if (!tokens)
		return (NULL);
	init_tokens(tokens);

	//--- approach changed...........................
	/* splits = ft_split(input, ' ');
	if (!splits)
		return (NULL);
	ft_tokenization(splits, tokens);   .............*/
	
	ft_lexer(input, tokens);
	ft_free_splits(splits); // this function is TO DO
	return (tokens);
}
/*
//Tokenization of each splitted "word"
void	ft_tokenization(char **splits, t_lst_token *tokens)
{
	int	 i;
	
	i = 0;
	while (splits[i])
	{
		t_token *token;
		
		token = new_token(splits[i], get_token_type(splits[i]));
		if (!token)
			return (NULL);
		if (!tokens->head)
			tokens->head = token;
		else
			tokens->tail->next = token;
		tokens->tail = token;
		tokens->size++;
		i++;
	}
}
*/