/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:27:35 by jorgutie          #+#    #+#             */
/*   Updated: 2025/02/17 18:35:13 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int unmatched_quotes(char *input)
{
	int i;
	char quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && !quote)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

static int check_invalid_pipes(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && (i == 0 || input[i + 1] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

int syntax_check(char *input)
{
	if (unmatched_quotes(input))
	{
		printf(RED"Syntax error: unmatched quotes\n"RESET);
		return (1);
	}
	if (check_invalid_pipes(input))
	{
		printf(RED"Syntax error: invalid pipe usage\n"RESET);
		return (1);
	}
	return (0);
}

ft_pu