/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:52:16 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:52:17 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (PIPE);
	if (!ft_strcmp(word, "<"))
		return (REDIR_IN);
	if (!ft_strcmp(word, ">"))
		return (REDIR_OUT);
	if (!ft_strcmp(word, ">>"))
		return (APPEND);
	if (!ft_strcmp(word, "<<"))
		return (HEREDOC);
	if (word[0] == '\"')
		return (DBQ);
	if (word[0] == '\'')
		return (SGQ);
	if (word[0] == ' ')
		return (SPC);
	return (WORD);
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

// Basic extraction of a word until found other types.
char	*extract_word(int *i, char *input)
{
	int	start;

	start = *i;
	while (input[*i] && (input[*i] != ' ' && input[*i] != '\''
			&& input[*i] != '"' && input[*i] != '|'
			&& input[*i] != '<' && input[*i] != '>'))
	{
		(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

// Extract operators:
// First Handle ">>" then "<<" and 
// finally single ">" or "<" or "|"
char	*extract_operator(int *i, char *input)
{
	int	start;

	start = *i;
	if (input[*i] == '>' && input[*i + 1] == '>')
		*i += 2;
	else if (input[*i] == '<' && input[*i + 1] == '<')
		*i += 2;
	else
		(*i)++;
	return (ft_substr(input, start, *i - start));
}
