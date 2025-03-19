#include "minishell.h"
#include "parsing.h"

/// to print List cmds TO DEBUG...............................

// Prints the full command list from minishell struct
void	print_command_list(t_lst_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	if (!cmd_list || !cmd_list->head)
	{
		printf(RED"No commands parsed.\n"RESET);
		return ;
	}
	printf(BOLD CYAN"\n----- PARSED COMMAND LIST -----\n"RESET);
	cmd = cmd_list->head;
	j = 0;
	while (cmd)
	{
		printf(GREEN"\nCommand[%d]:\n"RESET, j);
		if (!cmd->cmd_arr) {
			printf(BLUE"  [No command arguments]\n"RESET);
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
				printf(YELLOW"  RDir: Type: %d  Name: %s\n"RESET, 
					(int)redir->type, redir->name);
				redir = redir->next;
			}
		}

		if (cmd->next)
			printf(ORANGE"\n| (Pipe to next command)\n"RESET);
		cmd = cmd->next;
		j++;
	}
	
	printf(BOLD CYAN"\n----- END OF COMMAND LIST -----\n"RESET);
}
// ................................................... END OF PRINTING CMD LIST


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

// Initialize the Rdir List
int	init_redirection_list(t_cmd *cmd)
{
	cmd->list_rdir = malloc(sizeof(t_lst_rdir));
	if (!cmd->list_rdir)
		return (0);
	cmd->list_rdir->size = 0;
	cmd->list_rdir->head = NULL;
	cmd->list_rdir->tail = NULL;
	return (1);
}

// Fecth the name from the token
char	*get_redir_name(t_token *token)
{
	char	*name;

	if (token->next->type == SPC)
	{
		if (token->next->next)
			name = ft_strdup(token->next->next->value);
		else
			name = NULL;
	}
	else
		name = ft_strdup(token->next->value);
	return (name);
}

// Initializes the cmd->cmd_arr array with the first argument.
// Returns 1 on success, 0 on failure.
int	init_cmd_arr(t_cmd *cmd, char *arg)
{
	cmd->cmd_arr = malloc(sizeof(char *) * 2);
	if (!cmd->cmd_arr)
	{
		printf(RED "Error: Failed to allocate memory for cmd_arr\n" RESET);
		return (0);
	}
	cmd->cmd_arr[0] = ft_strdup(arg);
	if (!cmd->cmd_arr[0])
	{
		printf(RED"Error: Failed to duplicate and add arg\n"RESET);
		free(cmd->cmd_arr);
		cmd->cmd_arr = NULL;
		return (0);
	}
	cmd->cmd_arr[1] = NULL;
	return (1);
}

// Expands the existing `cmd->cmd_arr` by appending a new argument.
// Allocates memory for a new array, copies the old arguments,
// and appends the new argument.Returns the new array on success, 
// or NULL on failure.
char	**expand_cmd_arr(char **old_arr, char *arg)
{
	int		count;
	char	**new_arr;
	int		i;

	count = 0;
	while (old_arr[count])
		count++;
	new_arr = malloc(sizeof(char *) * (count + 2));
	if (!new_arr)
		return (printf(RED"Error: Failed to alloc memory.\n"RESET), NULL);
	i = -1;
	while (++i < count)
		new_arr[i] = old_arr[i];
	new_arr[i] = ft_strdup(arg);
	if (!new_arr[i])
		return (printf(RED"Error: Duplic arg.\n"RESET), free(new_arr), NULL);
	new_arr[i + 1] = NULL;
	return (new_arr);
}
