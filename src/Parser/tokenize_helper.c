
#include "minishell.h"
#include "parsing.h"

// Skip spaces in the input
void	skip_spaces(const char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
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
char *extract_word(int *i, char *input)
{
	int start = *i;
	char quote = 0;

	while (input[*i] && (input[*i] != ' ' || quote))
	{
		if ((input[*i] == '\'' || input[*i] == '"') && !quote)
			quote = input[*i]; // Open quote
		else if (input[*i] == quote)
			quote = 0; // Close quote
		(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

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
