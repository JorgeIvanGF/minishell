#include "minishell.h"
#include "parsing.h"

// Add the command to the list of commands
void	add_command(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	if (!cmd_list || !cmd)
		return ;
	if (!cmd_list->head)
		cmd_list->head = cmd;
	else
		cmd_list->tail->next = cmd;
	cmd_list->tail = cmd;
	cmd_list->size++;
}



// Adds an argument to the command's argument array (cmd_arr).
// If cmd_arr is not initialized, it initializes it; 
// otherwise, it expands the array.
void	add_argument(t_cmd *cmd, char *arg)
{
	char	**new_args;

	if (!cmd || !arg)
	{
		printf(RED"Error: NULL cmd or arg\n"RESET);
		return ;
	}
	if (!cmd->cmd_arr)
	{
		if (!init_cmd_arr(cmd, arg))
			return ;
		return ;
	}
	new_args = expand_cmd_arr(cmd->cmd_arr, arg);
	if (!new_args)
		return ;
	free(cmd->cmd_arr);
	cmd->cmd_arr = new_args;
}

// Add the RD to the list of RDs
// Create the instance of redir and set their fields using token's fields
// if it's the first set as it
void	add_redirection(t_cmd *cmd, t_token *token)
{
	t_rdir	*redir;

	if (!cmd->list_rdir && !init_redirection_list(cmd))
		return ;
	redir = malloc(sizeof(t_rdir));
	if (!redir)
		return ;
	redir->type = (t_rdir_type)token->type;
	redir->name = get_redir_name(token);
	if (!redir->name)
	{
		free(redir);
		return ;
	}
	redir->next = NULL;
	if (!cmd->list_rdir->head)
		cmd->list_rdir->head = redir;
	else
		cmd->list_rdir->tail->next = redir; // make the curr tail->Next to point to the new node
	cmd->list_rdir->tail = redir; // tail node updated to point to the new node
	cmd->list_rdir->size++; // update the size of the list after added the new node

	//printf(YELLOW"Added redirection: %s -> %s\n"RESET, token->value, redir->name); // To debug
}

// Create a new command object and initialize its members
t_cmd	*new_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_arr = NULL;

	// Allocate and initialize the list of redirections properly
	cmd->list_rdir = malloc(sizeof(t_lst_rdir));
	if (!cmd->list_rdir)
	{
		free(cmd);
		return (NULL);
	}
	cmd->list_rdir->size = 0;
	cmd->list_rdir->head = NULL;
	cmd->list_rdir->tail = NULL;
	cmd->next = NULL;
	return (cmd);
}

// initialize list of commands
void	init_lst_cmd(t_minishell *minishell)
{
	minishell->list_cmd = malloc(sizeof(t_lst_cmd));
	if (!minishell->list_cmd)
	{
		//minishell->list_cmd = NULL;
		return ;
	}
	minishell->list_cmd->head = NULL;
	minishell->list_cmd->tail = NULL;
	minishell->list_cmd->size = 0;
}

// Initialize parser and check tokens
t_lst_cmd	*parser(t_lst_token *tokens, t_minishell *minishell)
{
	t_token	*curr;
	t_cmd	*cmd;

	if (!tokens || !tokens->head)
	{
		printf(RED"No tokens to parse.\n"RESET);
		return (NULL);
	}
	init_lst_cmd(minishell);
	if (!minishell->list_cmd)
		return (NULL);
	cmd = new_command();
	if (!cmd)
		return (NULL);
	curr = tokens->head;
	return (process_tokens(curr, cmd, minishell));
}