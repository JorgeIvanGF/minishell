/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:52:04 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:52:05 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

// Double quotes: 
char	*extract_dq(int *i, char *input)// aqui check y extract new
{
	int		start;
	char	*word;

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
	int		start;
	char	*word;

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

// Extract Spaces: Create a token for space (using strdup to be freed later)
// Advance 'i' past all spaces (compresses contiguous spaces into one token)
char	*extract_spc(int *i, char *input)
{
	char	*word;

	word = ft_strdup(" ");
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	return (word);
}

// The extractor:
// Check: Space -> Operator -> Double quoted(check & extract new token)
// -> Single quoted(check & extract new token -> Normal command/arg
// 
char	*extractor(int *i, char *input)
{
	char	*word;

	if (input[*i] == ' ')
		word = extract_spc(i, input);
	else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		word = extract_operator(i, input);
	else if (input[*i] == '"')
		word = extract_dq(i, input);
	else if (input[*i] == '\'')
		word = extract_sq(i, input);
	else
		word = extract_word(i, input);
	return (word);
}
