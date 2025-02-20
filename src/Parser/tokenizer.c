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

// Process the word (create and add token and token type)
int	process_word(char *word, t_lst_token *tokens)
{
	if (!word)
		return (0);
	if (!add_token_to_list(word, tokens))
	{
		free(word);
		word = NULL;
		return (0);
	}
	free(word);
	word = NULL;
	return (1);
}

// Lexer in action: Skip spaces, extract operator or "word" then
// add to token list acoording to its type
int	ft_lexer(char *input, t_lst_token *tokens)
{
	int		i;
	char	*word;
	//t_token	*token;
	
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
			return (0);
		//token = new_token(word, get_token_type(word)); //Add token
		if (!process_word(word, tokens))
			return (0);
	}
	return (1);
}

// To free all the tokens in the list, and also the list itself
void	free_token_list(t_lst_token *tokens)
{
	t_token *curr;
	t_token *next;

	if (!tokens)
		return;
	curr = tokens->head;
	while (curr)
	{
		next = curr->next;
		free(curr->value);
		free(curr);
		curr = next;
	}
	free(tokens);
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
