#include "minishell.h"
#include "parsing.h"

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
	if (input[*i] != '"')
	{
		printf(RED"Syntax error: Unmatched double quotes\n"RESET);
		return (NULL);
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
	if (input[*i] != '\'')
	{
		printf(RED"Syntax error: Unmatched single quotes\n"RESET);
		return (NULL);
	}
	(*i)++;
	word = ft_substr(input, start, *i - start);
	return (word);
}

// Spaces: Create a token for space (using strdup so that it can be freed later)
// Advance 'i' past all spaces (this compresses contiguous spaces into one token)
char	*extract_spc(int *i, char *input)
{
	char *word;
	
	word = ft_strdup(" ");
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	return (word);
}

char	*extractor(int *i, char *input)
{
	char *word;

	if (input[*i] == ' ') // Space char
			word = extract_spc(i, input);
	else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>') //Special character
		word = extract_operator(i, input);
	else if (input[*i] == '"' ) //Doublel character
		word = extract_dq(i, input);// aqui check y extract new token
	else if (input[*i] == '\'' ) // Single quotes
		word = extract_sq(i, input);// aqui check y extract new token
	else
		word = extract_word(i, input); // Normal command/arg
	return (word);
}