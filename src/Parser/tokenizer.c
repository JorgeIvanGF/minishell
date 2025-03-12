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

// ************** NEW EXTRAXT REDIR FILENAME *********************

// This function extracts a complete redirection filename by concatenating unquoted and quoted segments.
char *extract_redir_filename(int *i, char *input)
{
	char *result;
	char *segment;
	int start;

	// Start with an empty string.
	result = ft_strdup("");
	if (!result)
		return (NULL);
		
	// Continue until a delimiter is encountered.
	while (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
		   input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			// Handle quoted segment.
			char quote = input[*i];
			(*i)++; // Skip the opening quote.
			start = *i;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			segment = ft_substr(input, start, *i - start);
			if (input[*i] == quote)
				(*i)++; // Skip the closing quote.
		}
		else
		{
			// Handle unquoted segment.
			start = *i;
			while (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
				   input[*i] != '<' && input[*i] != '>' &&
				   input[*i] != '\'' && input[*i] != '\"')
				(*i)++;
			segment = ft_substr(input, start, *i - start);
		}
		// Append the segment to the result.
		{
			char *temp = ft_strjoin(result, segment);
			free(result);
			result = temp;
			free(segment);
		}
	}
	return (result);
}

// *************************** MODSSSSS ****************************************************


// Function to process an operator token
static int process_operator(char *input, int *i, t_lst_token *tokens)
{
	char *word;
	t_token_type type;

	word = extract_operator(i, input);
	if (!word)
		return (0);
	if (!process_word(word, tokens))
		return (0);

	type = get_token_type(tokens->tail->value);
	if (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC)
	{
		skip_spaces(input, i);
		word = extract_redir_filename(i, input);
		if (!word)
			return (0);
		if (!process_word(word, tokens))
			return (0);
	}
	return (1);
}

// Function to process a standard token
static int process_standard_token(char *input, int *i, t_lst_token *tokens)
{
	char *word;

	word = extractor(i, input);
	if (!word)
		return (0);
	if (!process_word(word, tokens))
		return (0);
	return (1);
}

// Main lexer function
int ft_lexer(char *input, t_lst_token *tokens)
{
	int i;

	if (!input || !tokens)
		return (0);
	i = 0;
	while (input[i] && input[i] == ' ')// skip initial spaces
		i++;
	while (input[i])
	{
		if (!input[i])
			break;
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

// ********************************************** MODS ****************************************



// // ***** NEW *****  LEXER LOGIC MODIFIED ***************************
// int	ft_lexer(char *input, t_lst_token *tokens)
// {
// 	int				i;
// 	char			*word;
// 	t_token_type	type;

// 	if (!input || !tokens)
// 		return (0);
// 	i = 0;
// 	// Skip initial spaces only
// 	while (input[i] && input[i] == ' ')
// 		i++;
// 	while (input[i])
// 	{
// 		if (!input[i])
// 			break;
// 		// If current char is an operator.
// 		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
// 		{
// 			// Extract the operator token.
// 			word = extract_operator(&i, input);
// 			if (!word)
// 				return (0);
// 			if (!process_word(word, tokens))
// 				return (0);
			
			
// 			// Check if the operator is a redirection.
// 			type = get_token_type(tokens->tail->value);
// 			if (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC)
// 			{
// 				// Skip any spaces after the operator.
// 				skip_spaces(input, &i);
// 				// Extract the entire redirection filename.
// 				word = extract_redir_filename(&i, input);
// 				if (!word)
// 					return (0);
// 				if (!process_word(word, tokens))
// 					return (0);
// 			}
// 		}
// 		else
// 		{
// 			// Otherwise, use the standard extractor.
// 			word = extractor(&i, input);
// 			if (!word)
// 				return (0);
// 			if (!process_word(word, tokens))
// 				return (0);
// 		}
// 	}
// 	return (1);
// }


// // LEXER LOGIC MODIFIED
// int	ft_lexer(char *input, t_lst_token *tokens)
// {
// 	int		i;
// 	char	*word;

// 	if (!input || !tokens)
// 		return (0);
// 	i = 0;
// 	// Skip initial spaces only
// 	while (input[i] && input[i] == ' ')
// 		i++;
// 	while (input[i])
// 	{
// 		if (!input[i])
// 			break;
// 		word = extractor(&i, input);
// 		if (!word)
// 			return (0);
// 		//token = new_token(word, get_token_type(word)); //Add token
// 		//printf(GREEN"word = %s\n"RESET, word);
// 		if (!process_word(word, tokens))
// 			return (0);
// 	}
// 	return (1);
// }


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



