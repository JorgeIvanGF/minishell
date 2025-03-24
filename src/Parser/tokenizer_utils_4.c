#include "minishell.h"
#include "parsing.h"

// Appends the string 'segment' to 'result' by concatenating them,
// frees the memory allocated for both 'result' and 'segment',
// and returns the newly allocated concatenated string.
char	*append_segment(char *result, char *segment)
{
	char	*temp;

	temp = ft_strjoin(result, segment);
	free(result);
	free(segment);
	return (temp);
}

int	is_redirection(const char *token)
{
	return ((ft_strcmp(token, ">") == 0)
			|| (ft_strcmp(token, ">>") == 0)
			|| (ft_strcmp(token, "<") == 0)
			|| (ft_strcmp(token, "<<") == 0));
}

// Check redirection syntax:
// Skip any SPC tokens -> If there's no valid token after the redir operator,
// or the token is not of a type that can be a file/delimiter,
// or its value is empty, then it's a syntax error.
int	check_redirection_syntax(t_lst_token *token_list)
{
	t_token	*tmp;
	t_token	*next;

	tmp = token_list->head;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT ||
			tmp->type == APPEND || tmp->type == HEREDOC)
		{
			next = tmp->next;
			while (next && next->type == SPC)
				next = next->next;
			if (!next || ((next->type != WORD && next->type != DBQ &&
				next->type != SGQ) || !next->value || next->value[0] == '\0'))
			{
				ft_putstr_fd(RED"Error: syntax error near unexpected token `newline'\n"RESET, 2);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
