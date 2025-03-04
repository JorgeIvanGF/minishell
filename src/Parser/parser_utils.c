#include "minishell.h"
#include "parsing.h"

/// to print List cmds TO DEBUG......................................................

// Prints the full command list from minishell struct
void    print_command_list(t_lst_cmd *cmd_list)
{
	t_cmd *cmd;
	int i;
	int j;

	if (!cmd_list || !cmd_list->head)
	{
		printf(RED"No commands parsed.\n"RESET);
		return;
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