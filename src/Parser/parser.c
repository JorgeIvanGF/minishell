#include "minishell.h"
#include "parsing.h"

// Add the command to the list of commands
void	add_command(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	if (!cmd_list->head)
		cmd_list->head = cmd;
	else
		cmd_list->tail->next = cmd;
	cmd_list->tail = cmd;
	cmd_list->size++;
}

// Add the arg to cmd array
void	add_argument(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (cmd->cmd_arr && cmd->cmd_arr[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	i = 0;
	while (cmd->cmd_arr && cmd->cmd_arr[i])
	{
		new_args[i] = cmd->cmd_arr[i];
		i++;
	}
	new_args[i] = ft_strdup(arg); // Store the argument
	if (!new_args[i])
	{
		// Need to free previously allocated memory
		while (--i >= 0)
			free(new_args[i]);
		free(new_args);
		return;
	}
	new_args[i + 1] = NULL;
	free(cmd->cmd_arr); // delete the old array
	cmd->cmd_arr = new_args; // update the new array including the added arg
	printf(GREEN"Added argument: %s\n"RESET, arg); // To debug
}

// Add the RD to the list of RDs
// Create the instance of redir and set their fields using token's fields
// if it's the first set as it
void	add_redirection(t_cmd *cmd, t_token *token)
{
	t_rdir	*redir;

	/* if (!cmd->list_rdir)// POSSIBLE: In case is not allocated in new command
	{
		cmd->list_rdir = malloc(sizeof(t_lst_rdir));
		if (!cmd->list_rdir)
			return ;
		cmd->list_rdir->head = NULL;
		cmd->list_rdir->tail = NULL;
		cmd->list_rdir->size = 0;
	} */
	redir = malloc(sizeof(t_rdir));
	if (!redir)
		return ;
	redir->type = (t_rdir_type)token->type; //************ */
	redir->name = ft_strdup(token->next->value);
	//freee
	if (!redir->name)
		return (free(redir));
	redir->next = NULL;
	if (!cmd->list_rdir->head)
		cmd->list_rdir->head = redir;
	else
		cmd->list_rdir->tail->next = redir; // make the curr tail->Next to point to the new node
	cmd->list_rdir->tail = redir; // tail node updated to point to the new node
	cmd->list_rdir->size++; // update the size of the list after added the new node

	printf(YELLOW"Added redirection: %s -> %s\n"RESET, token->value, redir->name); // To debug
}

// Create a new command object and initialize its members
t_cmd	*new_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_arr = NULL;
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



//Main Parser Function: Convert tokens to commands
void	parser(t_lst_token *tokens, t_minishell *minishell)
{
	t_token	*curr;
	t_cmd	*cmd;

	if (!tokens || !tokens->head)
	{
		printf(RED"No tokens to parse.\n"RESET);// TO DEBUG
		return ;
	}
		
	init_lst_cmd(minishell);
	if (!minishell->list_cmd)
		return ;
	cmd = new_command(); // creates and initialize it
	if (!cmd)
		return ;
	curr = tokens->head;
	while (curr)
	{
		if (curr->type == WORD)
		{
			//TO DEBUG
			printf(MAG"\nProcessing token: [%s] | Type: %d\n"RESET, curr->value, curr->type);

			// Ensure the creation of the array cmd
			if (!cmd->cmd_arr)
				cmd->cmd_arr = malloc(sizeof(char *) * 2); // 1)for the arg and 2)for NULL terminate
			add_argument(cmd, curr->value);
		}
		else if (curr->type >= REDIR_IN && curr->type <= HEREDOC)// it adresses all REDIRs 
		{
			if (!curr->next || curr->next->type != WORD)
			{
				printf("Syntax error: missing file after '%s'\n", curr->value);
				// free cmd
				return ;
			}
			add_redirection(cmd, curr);
			curr = curr->next; // Skip the filename token
		}
		else if (curr->type == PIPE)
		{
			add_command(minishell->list_cmd, cmd);
			printf(BLUE"\nAdded command before PIPE.\n"RESET); //TO DEBUG
			cmd = new_command();
		}
		curr = curr->next;
	}
	add_command(minishell->list_cmd, cmd);
	printf(GREEN"\nParsing complete!\n"RESET); // TO DEBUG

	// To print the cmd array
	printf(YELLOW"Cmd Array (Last one): \n"RESET);
	int i = 0;
	while (cmd->cmd_arr && cmd->cmd_arr[i])
	{
		printf("arr[%d] = %s\n", i, cmd->cmd_arr[i]);
		i++;
	}

	//print_command_list(minishell->list_cmd);
}

/* void	ft_copy_env(t_minishell *shell, char **env)
{
	
}
*/

