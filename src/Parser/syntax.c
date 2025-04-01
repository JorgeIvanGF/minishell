/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:52:01 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:52:02 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// Rule 1: First token cant be PIPE but it could be a REDIR
static int	check_first_token(t_lst_token *tokens)
{
	if (tokens->head->type == PIPE)
	{
		printf(RED"Syntax error: invalid start with '%s'\n"RESET,
			tokens->head->value);
		return (1);
	}
	return (0);
}

// Rule 2: Double pipes are not allowed (||)
static int	check_double_pipes(t_token *curr)
{
	while (curr)
	{
		if (curr->type == PIPE && curr->next && curr->next->type == PIPE)
		{
			printf(RED"Syntax error: Invalid pipe usage\n"RESET);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

// Rule 3: Redirections must be followed by a WORD or SPC
// also skipped other SPCs
static int	check_redirections(t_token *curr)
{
	t_token	*next;

	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == REDIR_OUT
			|| curr->type == APPEND || curr->type == HEREDOC)
		{
			next = curr->next;
			while (next && next->type == SPC)
				next = next->next;
			if (!next || next->type != WORD)
			{
				printf(RED"Syntax error: missing file after '%s'\n"RESET,
					curr->value);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

// Rule 4: Last token cannot be an Operator
static int	check_last_token(t_token *curr)
{
	while (curr->next)
		curr = curr->next;
	if (curr->type == PIPE || curr->type == REDIR_IN || curr->type == REDIR_OUT
		|| curr->type == APPEND || curr->type == HEREDOC)
	{
		printf(RED"Syntax error: unexpected '%s'\n"RESET, curr->value);
		return (1);
	}
	return (0);
}

// Main Syntax check function:
// No tokens, no syntax error
int	syntax_check(t_lst_token *tokens, t_minishell *minishell)
{
	t_token	*curr;

	if (!tokens || !tokens->head)
		return (0);
	if (check_first_token(tokens))
		return (1);
	if (check_double_pipes(tokens->head))
		return (1);
	if (check_redirections(tokens->head))
		return (1);
	if (check_last_token(tokens->head))
		return (1);
	curr = tokens->head;
	while (curr)
	{
		if (curr->type == DBQ || curr->type == WORD)
			expand_variables(curr, minishell->env, minishell);
		remove_external_quotes(curr);
		curr = curr->next;
	}
	return (0);
}
