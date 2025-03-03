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
// // Rule 3: Redirections must be followed by a WORD
// static int	check_redirections(t_token *curr)
// {
// 	while (curr)
// 	{
// 		if ((curr->type == REDIR_IN || curr->type == REDIR_OUT ||
// 			 curr->type == APPEND || curr->type == HEREDOC) &&
// 			(!curr->next || (curr->next->type != WORD && curr->next->type != SPC)))//handle space too
// 		{
// 			printf(RED"Syntax error: missing file after '%s'\n"RESET, curr->value);
// 			return (1);
// 		}
// 		curr = curr->next;
// 	}
// 	return (0);
// }


// **************** MODIFY REDIR ****************

static int	check_redirections(t_token *curr)
{
	t_token *next;

	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == REDIR_OUT ||
			curr->type == APPEND || curr->type == HEREDOC)
		{
			next = curr->next;
			// Skip over any SPC tokens
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
	if (curr->type == PIPE || curr->type == REDIR_IN || curr->type == REDIR_OUT ||
		curr->type == APPEND || curr->type == HEREDOC)
	{
		printf(RED"Syntax error: unexpected '%s'\n"RESET, curr->value);
		return (1);
	}
	return (0);
}

int	syntax_check(t_lst_token *tokens, t_minishell *minishell)
{
	t_token *curr;

	if (!tokens || !tokens->head)
		return (0); // No tokens, no syntax error
	if (check_first_token(tokens))
		return (1);
	if (check_double_pipes(tokens->head))
		return (1);
	if (check_redirections(tokens->head))
		return (1);
	if (check_last_token(tokens->head))
		return (1);
	curr = tokens->head;
	int i = 0;

	// while (curr)
	// {
	// 	//printf(GREEN"\nToken [%d]...\n"RESET, i);
	// 	expand_variables(curr, minishell->env);
	// 	remove_external_quotes(curr);		
	// 	curr = curr->next;
	// 	i++;
	// }

	while (curr)
	{
		//printf(GREEN"\nToken [%d]...\n"RESET, i);
		if (curr->type == DBQ || curr->type == WORD)
			expand_variables(curr, minishell->env);
		remove_external_quotes(curr);		
		curr = curr->next;
		i++;
	}
	return (0);
}
