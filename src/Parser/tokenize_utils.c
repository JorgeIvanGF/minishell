
#include "minishell.h"
#include "parsing.h"

// Skip spaces in the input
void	skip_spaces(const char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

// Skip spaces in the input
void	skip_spaces_2(const char *input, int **i)
{
	while (input[**i] == ' ')
		(**i)++;
}

// Get the token type (based on the enum)
t_token_type	get_token_type(char *word)
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
	if (word[0] == '\"') // Para Double Quotes
		return DBQ;
	if (word[0] == '\'') // Para Single Quotes
		return DBQ;
	if (word[0] == ' ') // Para Spaces
		return SPC;
	return WORD;
}

// Creation of a token with malloc and assign the type
t_token	*new_token(char *value, t_token_type type)
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

// Extract Normal Words (Handles Quotes Too!)
// the loop continues as long as: Not reach the end of string
// and either curr char isnt space or we are inside quotes(quote is non-zero)
// char	*extract_word(int *i, char *input)
// {
// 	int start;
// 	char quote; 

// 	start = *i;
// 	quote = 0;// (quote tracker (0 = NO open quote)
// 	while (input[*i] && (input[*i] != ' ' || quote))
// 	{
// 		if ((input[*i] == '\'' || input[*i] == '"'))
// 		{
// 			if (!quote) // If no inside quote, start quot mode
// 				quote = input[*i]; // Open quote
// 			else if (input[*i] == quote)
// 				quote = 0; // Close quote
// 		}
// 		(*i)++;
// 	}
// 	// If quote is still open, return NULL to indicate syntax error
// 	if (quote)
// 	{
// 		printf(MAG"Syntax error: Unmatched quotes\n"RESET);
// 		return (NULL);
// 	}
// 	return (ft_substr(input, start, *i - start));
// }

//*************** EXTTRACT WORD MODFIED ********************

char	*extract_word(int *i, char *input)
{
	int start;

	start = *i; // ***REVISAR SI EL ESPACIO SE NECESITA VERIFICAR O NO 
	while (input[*i] && (input[*i] != ' ' && input[*i] != '\'' && input[*i] != '"'
			&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>'))
	{
		(*i)++;
	}
	//printf(CYAN"word = %s\n"RESET,ft_substr(input, start, *i - start));
	return (ft_substr(input, start, *i - start));
}
// *****************************************************


// Extract operators
char *extract_operator(int *i, char *input)
{
	int start = *i;

	if (input[*i] == '>' && input[*i + 1] == '>')
		*i += 2; // Handle ">>"
	else if (input[*i] == '<' && input[*i + 1] == '<')
		*i += 2; // Handle "<<"
	else
		(*i)++; // Handle single ">" or "<" or "|"

	return (ft_substr(input, start, *i - start));
}
