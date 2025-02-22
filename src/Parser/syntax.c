#include "minishell.h"
#include "parsing.h"

int	syntax_check(t_lst_token *tokens)
{
	t_token *curr;

	if (!tokens || !tokens->head)
		return (0); // No tokens, no syntax error

	curr = tokens->head;

	// Rule 1: First token cant be PIPE but it could be a REDIR
	if (curr->type == PIPE)
	{
		printf(RED"Syntax error: invalid start with '%s'\n"RED, curr->value);
		return (1);
	}

	while (curr) // through all the tokens
	{
		// Rule 2: Double pipes are not allowed (||)
		if (curr->type == PIPE && curr->next && curr->next->type == PIPE)
		{
			printf(RED"Syntax error: Invalid pipe usage\n"RESET);
			return (1);
		}
		// Rule 3: Redirections must be followed by a WORD
		if ((curr->type == REDIR_IN || curr->type == REDIR_OUT
				|| curr->type == APPEND || curr->type == HEREDOC)
			&& (!curr->next || curr->next->type != WORD)) //****** */ revisar por cual lado empieza a verificar
		{
			printf(RED"Syntax error: missing file after '%s'\n"RESET, curr->value);
			return (1);
		}
		// Rule 4: Last token cannot be a PIPE or Redirection ******** solo se necesita test el pipe arriba ya se hizo
		if (!curr->next && (curr->type == PIPE || curr->type == REDIR_IN
				|| curr->type == REDIR_OUT || curr->type == APPEND
				|| curr->type == HEREDOC))
		{
			printf(RED"Syntax error: unexpected '%s'\n"RESET, curr->value);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

	/* if (unmatched_quotes(input))
	{
		printf(RED"Syntax error: unmatched quotes\n"RESET);
		return (1);
	}
	if (check_invalid_pipes(input))
	{
		printf(RED"Syntax error: invalid pipe usage\n"RESET);
		return (1);
	}
	*/


