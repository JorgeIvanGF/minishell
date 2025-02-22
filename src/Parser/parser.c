#include "minishell.h"
#include "parsing.h"

// Add the command to the list of commands
void	add_command(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	if (!cmd_list || !cmd)
		return;
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

	if (!cmd || !arg) //added to check
	{
		printf(RED"Error: add_argument() received NULL cmd or arg\n"RESET);
		return ;
	}

	// Ensure cmd->cmd_arr is initialized before using it
	if (!cmd->cmd_arr)
	{
		cmd->cmd_arr = malloc(sizeof(char *) * 2);
		if (!cmd->cmd_arr)
		{
			printf(RED"Error: Failed to allocate memory for cmd_arr\n"RESET);
			return ;
		}
		cmd->cmd_arr[0] = ft_strdup(arg);

		// to DEBUG
		if (!cmd->cmd_arr[0])
		{
			printf("Error: Failed to add arg\n");
			return ;
		}
		cmd->cmd_arr[1] = NULL;
		printf(GREEN"Added first argument: %s\n"RESET, arg);
		return ;
	}

	// Here we access cmd->cmd_arr, but it might contain uninitialized values!
	i = 0;
	while (cmd->cmd_arr && cmd->cmd_arr[i]) // <-- This loop depends on uninitialized memory!
		i++;
	
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
	{
		printf(RED"Error: Failed to allocate memory for new arguments.\n"RESET);
		return;
	}
	i = 0;
	while (cmd->cmd_arr && cmd->cmd_arr[i]) // <-- Again, we access uninitialized memory!
	{
		new_args[i] = cmd->cmd_arr[i];
		i++;
	}
	new_args[i] = ft_strdup(arg); // Store the argument
	if (!new_args[i])
	{
		printf(RED"Error: Failed to allocate memory for argument copy.\n"RESET);
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

	// check if not initialized
	if (!cmd->list_rdir)  // Prevent invalid memory access
	{
		cmd->list_rdir = malloc(sizeof(t_lst_rdir));
		if (!cmd->list_rdir)
			return ;
		cmd->list_rdir->size = 0;
		cmd->list_rdir->head = NULL;
		cmd->list_rdir->tail = NULL;
	}

	redir = malloc(sizeof(t_rdir));
	if (!redir)
		return ;
	redir->type = (t_rdir_type)token->type; //************ 
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



/// to print List cmds TO DEBUG......................................................

// Prints a single command with its arguments
void print_command(t_cmd *cmd)
{
	int i = 0;
	
	printf(GREEN"\nCommand: "RESET);
	if (!cmd->cmd_arr)
		printf(RED"[No command arguments]\n"RESET);
	else
	{
		while (cmd->cmd_arr[i])
		{
			printf(BLUE"%s "RESET, cmd->cmd_arr[i]);
			i++;
		}
		printf("\n");
	}
}

// Print RDs
void print_redirections(t_lst_rdir *list_rdir)
{
	t_rdir *redir;

	if (!list_rdir || !list_rdir->head)
	{
		printf(YELLOW"  [No redirections]\n"RESET);
		return;
	}
	
	redir = list_rdir->head;
	while (redir)
	{
		printf(YELLOW"  Redirection: %s -> %s\n"RESET, 
			   (redir->type == RD_IN) ? "<" :
			   (redir->type == RD_OUT) ? ">" :
			   (redir->type == RD_APND) ? ">>" : "<<",
			   redir->name);
		redir = redir->next;
	}
}


// Prints the full command list from minishell struct
void print_command_list(t_lst_cmd *cmd_list)
{
	t_cmd *cmd;
	int i;

	if (!cmd_list || !cmd_list->head)
	{
		printf(RED"No commands parsed.\n"RESET);
		return;
	}

	printf(GREEN"\n--- Parsed Command List ---\n"RESET);
	cmd = cmd_list->head;

	while (cmd)
	{
		printf(GREEN"\nCommand:\n"RESET);
		if (!cmd->cmd_arr) {
			printf(RED"  [No command arguments]\n"RESET);
		} else {
			for (i = 0; cmd->cmd_arr[i]; i++)
				printf(BLUE"  Arg[%d]: %s\n"RESET, i, cmd->cmd_arr[i]);
		}

		// Check if redirections exist before printing
		if (!cmd->list_rdir) {
			printf(YELLOW"  [No redirections list]\n"RESET);
		} else if (!cmd->list_rdir->head) {
			printf(YELLOW"  [No redirections]\n"RESET);
		} else {
			t_rdir *redir = cmd->list_rdir->head;
			while (redir)
			{
				printf(YELLOW"  Redirection: %s -> %s\n"RESET, 
					(redir->type == RD_IN) ? "<" :
					(redir->type == RD_OUT) ? ">" :
					(redir->type == RD_APND) ? ">>" : "<<",
					redir->name);
				redir = redir->next;
			}
		}

		if (cmd->next)
			printf(ORANGE"\n| (Pipe to next command)\n"RESET);
		cmd = cmd->next;
	}
	
	printf(GREEN"--- End of Command List ---\n"RESET);
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
		//printf(B_RED"aquí\n"RESET);
		if (curr->type == WORD)
		{

			//TO DEBUG
			printf(MAG"\nProcessing token: [%s] | Type: %d\n"RESET, curr->value, curr->type);

			// Ensure the creation of the array cmd
			if (!cmd->cmd_arr) // POSSIBLE ERROR: may be allocating uninitialized memory
				cmd->cmd_arr = malloc(sizeof(char *) * 2); // 1)for the arg and 2)for NULL terminate
			
			// ******* HERE WAS THE PROBLEM: ******************** 
			// cmd array was allocated but never initialized//
			cmd->cmd_arr[0] = NULL; // Explicitly initialize the array
			cmd->cmd_arr[1] = NULL;
			// ********************************************************** 

			add_argument(cmd, curr->value);

			// TO DEBUG
			printf(YELLOW"\nCmd Array (Current Command):\n"RESET);
			int j = 0;
			while (cmd->cmd_arr && cmd->cmd_arr[j])
			{
				printf("arr[%d] = %s\n", j, cmd->cmd_arr[j]);
				j++;
			}

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
			
			// TO DEBUG
			printf(YELLOW"\nCmd Array (Previous Command Before Pipe):\n"RESET);
			int k = 0;
			while (cmd->cmd_arr && cmd->cmd_arr[k])
			{
				printf("arr[%d] = %s\n", k, cmd->cmd_arr[k]);
				k++;
			}

			cmd = new_command();
		}
		curr = curr->next;
	}
	add_command(minishell->list_cmd, cmd);
	printf(GREEN"\nParsing complete!\n"RESET); // TO DEBUG


	// to identify if minishell->list_cmd is NULL
	if (!minishell->list_cmd)
	{
		printf(RED"Error: minishell->list_cmd is NULL!\n"RESET);
		return;
	}
	if (!minishell->list_cmd->head)
	{
		printf(RED"Error: No commands were added to the list!\n"RESET);
		return;
	}


	// To print the cmd array
	printf(YELLOW"Cmd Array (Last one): \n"RESET);
	int i = 0;
	while (cmd->cmd_arr && cmd->cmd_arr[i])
	{
		printf("arr[%d] = %s\n", i, cmd->cmd_arr[i]);
		i++;
	}


	print_command_list(minishell->list_cmd);
}


