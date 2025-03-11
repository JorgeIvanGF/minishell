#include "minishell.h"
#include "parsing.h"

t_lst_cmd	*finalize_parsing(t_minishell *minishell)
{
	if (!minishell->list_cmd)
	{
		printf(RED"Error: minishell->list_cmd is NULL!\n"RESET);
		return (NULL);
	}
	if (!minishell->list_cmd->head)
	{
		printf(RED"Error: No commands were added to the list!\n"RESET);
		return (NULL);
	}
	//print_command_list(minishell->list_cmd);
	return (minishell->list_cmd);
}

// Skip space tokens and return next non-space token 
t_token	*skip_spaces_(t_token *token)
{
	while (token && token->type == SPC)
		token = token->next;
	return (token);
}

// New handle redirection
t_token	*handle_redirection(t_token *curr, t_cmd *cmd, t_minishell *minishell)
{
	t_token	*next_token;

	if (!curr->next || (curr->next->type != WORD && curr->next->type != SPC))
	{
		printf("Syntax error: missing file after '%s'\n", curr->value);
		free_cmd_list(minishell->list_cmd);
		minishell->list_cmd = NULL;
		return (NULL);
	}
	next_token = skip_spaces_(curr->next);
	if (!next_token)
	{
		printf("Syntax error: missing file after '%s'\n", curr->value);
		free_cmd_list(minishell->list_cmd);
		minishell->list_cmd = NULL;
		return (NULL);
	}
	add_redirection(cmd, curr);
	return (next_token->next);
}

// Handle word, double quote, and single quote tokens
t_token	*handle_word_token(t_token *curr, t_cmd *cmd)
{
	char	*merged;

	merged = ft_strdup(curr->value);
	if (!merged)
		return (NULL);
	while (curr->next && (curr->next->type == WORD || 
		curr->next->type == DBQ || curr->next->type == SGQ))
	{
		char *temp = merged;
		merged = ft_strjoin(merged, curr->next->value);
		free(temp);
		if (!merged)
			return (NULL);
		curr = curr->next;
	}
	add_argument(cmd, merged);
	free(merged);
	return (curr->next);
}

// Process tokens and build commands
t_lst_cmd	*process_tokens(t_token *curr, t_cmd *cmd, t_minishell *minishell)
{
	while (curr)
	{
		if (curr->type == SPC)
		{
			curr = curr->next;
			continue ;
		}
		if (curr->type == WORD || curr->type == DBQ || curr->type == SGQ)
			curr = handle_word_token(curr, cmd);
		else if (curr->type >= REDIR_IN && curr->type <= HEREDOC)
			curr = handle_redirection(curr, cmd, minishell);
		else if (curr->type == PIPE)
		{
			add_command(minishell->list_cmd, cmd);
			cmd = new_command();
			if (!cmd)
				return (NULL);
			curr = curr->next;
		}
		else
			curr = curr->next;
	}
	add_command(minishell->list_cmd, cmd);
	return (finalize_parsing(minishell));
}
