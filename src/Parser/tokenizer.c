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

// // Lexer in action: Skip spaces, extract operator or "word" then
// // add to token list acoording to its type
// int	ft_lexer(char *input, t_lst_token *tokens)
// {
// 	int		i;
// 	char	*word;

// 	if (!input || !tokens)
// 		return (0);
// 	i = 0;
// 	while (input[i])
// 	{
// 		skip_spaces(input, &i);
// 		if (!input[i]) 
// 			break;
// 		if (input[i] == '|' || input[i] == '<' || input[i] == '>') //Special character
// 			word = extract_operator(&i, input);
// 		else
// 			word = extract_word(&i, input); // Normal command/arg
// 		if (!word)
// 			return (0);
// 		//token = new_token(word, get_token_type(word)); //Add token
// 		if (!process_word(word, tokens))
// 			return (0);
// 	}
// 	return (1);
// }

// ******************************MODIFICATION OF LEXER LOGIC****************************

// Double quotes: 
char	*extract_dq(int *i, char *input)// aqui check y extract new
{
	int start;
	char *word;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != '"')
	{
		(*i)++;
	}
	(*i)++;
	word = ft_substr(input, start, *i - start);
	return (word);
}

// Single quotes: 
char	*extract_sq(int *i, char *input)// aqui check y extract new
{
	int start;
	char *word;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		(*i)++;
	}
	(*i)++;
	word = ft_substr(input, start, *i - start);
	return (word);
}

// char *extract_spc(int *i, char *input)
// {
// 	char *word;

// 	word = ft_strdup(" ");  // Allocate memory for the space string
// 	skip_spaces_2(input, &i);
// 	return (word);
// }

char	*extract_spc(int *i, char *input)
{
	char *word;

	// Create a token for space (using strdup so that it can be freed later)
	word = ft_strdup(" ");
	// Advance i past all spaces (this compresses contiguous spaces into one token)
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	return (word);
}

// LEXER MODIFIED
int	ft_lexer(char *input, t_lst_token *tokens)
{
	int		i;
	char	*word;

	if (!input || !tokens)
		return (0);
	i = 0;
	// Skip initial spaces only
	while (input[i] && input[i] == ' ')
		i++;
	while (input[i])
	{
		// if (input[0] == ' ')
		// 	skip_spaces(input, &i);
		printf(ORANGE"i = %d\n"RESET, i);
		printf(ORANGE"word = %c\n"RESET, input[i]);
		if (!input[i]) 
			break;
		if (input[i] == ' ')
		{
			printf(ORANGE"ENTRA ESPACE\n"RESET);
			word = extract_spc(&i, input);
			printf(ORANGE"word = %s\n"RESET, word);
		}
			
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>') //Special character
			word = extract_operator(&i, input);
		else if (input[i] == '"' ) //Doublel character
			word = extract_dq(&i, input);// aqui check y extract new token
		else if (input[i] == '\'' ) // Single quotes
			word = extract_sq(&i, input);// aqui check y extract new token
		else
			word = extract_word(&i, input); // Normal command/arg
		if (!word)
			return (0);
		//token = new_token(word, get_token_type(word)); //Add token
		printf(GREEN"word = %s\n"RESET, word);
		if (!process_word(word, tokens))
			return (0);
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
