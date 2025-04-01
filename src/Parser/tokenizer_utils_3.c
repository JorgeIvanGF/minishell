/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:52:08 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:52:09 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// Extract a segment from 'input' that is enclosed by the 
// specified 'quote' character. It starts right after the 
// opening quote (advancing the index 'i'),and continues until 
// it finds the closing quote. Returns the extracted substring.
char	*extract_quoted(int *i, char *input, char quote)
{
	int		start;
	char	*segment;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	segment = ft_substr(input, start, *i - start);
	if (input[*i] == quote)
		(*i)++;
	return (segment);
}

// Extracts a segment from 'input' that is not enclosed in quotes.
// The segment is delimited by spaces, pipe, redirection symbols, or quotes.
// It starts at the current index 'i' and continues until a delimiter is found.
char	*extract_unquoted(int *i, char *input)
{
	int		start;
	char	*segment;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '\'' && input[*i] != '\"')
		(*i)++;
	segment = ft_substr(input, start, *i - start);
	return (segment);
}

// Extract a redirection filename handling quoted and 
// unquoted segments within the filename.It concatenates all segments 
// until a delimiter (space, pipe, or redirection operator) is encountered,
// and returns the resulting filename string.
char	*extract_redir_filename(int *i, char *input)
{
	char	*result;
	char	*segment;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (input[*i] && input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			segment = extract_quoted(i, input, input[*i]);
		else
			segment = extract_unquoted(i, input);
		if (!segment)
		{
			free(result);
			return (NULL);
		}
		result = append_segment(result, segment);
	}
	return (result);
}

// Function to process an operator token
int	process_operator(char *input, int *i, t_lst_token *tokens)
{
	char			*word;
	t_token_type	type;

	word = extract_operator(i, input);
	if (!word)
		return (0);
	if (!process_word(word, tokens))
		return (0);
	type = get_token_type(tokens->tail->value);
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC)
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
int	process_standard_token(char *input, int *i, t_lst_token *tokens)
{
	char	*word;

	word = extractor(i, input);
	if (!word)
		return (0);
	if (!process_word(word, tokens))
		return (0);
	return (1);
}
