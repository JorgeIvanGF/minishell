
#include "minishell.h"
#include "parsing.h"

// Free the list of redirections
void free_redirections(t_lst_rdir *list_rdir)
{
	t_rdir *tmp;
	t_rdir *redir;

	if (!list_rdir)
		return;

	redir = list_rdir->head;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->name);  // Free the filename string
		free(tmp);        // Free the redirection struct
	}
	list_rdir->head = NULL; // Set head to NULL after freeing
	free(list_rdir);  // Free the list itself
}

// Free a single command
void free_cmd(t_cmd *cmd)
{
	int i = 0;

	if (!cmd)
		return;
	
	if (cmd->cmd_arr) // Free command arguments
	{
		while (cmd->cmd_arr[i])
		{
			free(cmd->cmd_arr[i]); // Free each argument string
			cmd->cmd_arr[i] = NULL; // Prevent dangling pointers
			i++;
		}
		free(cmd->cmd_arr); // Free the array itself
		cmd->cmd_arr = NULL; // Avoid potential double free
	}

	// Free redirections safely
	if (cmd->list_rdir)
	{
		free_redirections(cmd->list_rdir);
		cmd->list_rdir = NULL; // Ensure it’s null after freeing
	}
	free(cmd); // Free the command struct
	cmd = NULL; // Avoid use after free
}

// Free the entire command list
void free_cmd_list(t_lst_cmd *cmd_list)
{
	t_cmd *cmd;
	t_cmd *tmp;

	if (!cmd_list)
		return;
	
	cmd = cmd_list->head;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_cmd(tmp); // Free each command
	}
	cmd_list->head = NULL; // Prevent accessing freed memory
	free(cmd_list); // Free the command list struct
}

// Free everything before exiting
void exit_shell(t_minishell *minishell)
{
	if (minishell->list_cmd)
	{
		free_cmd_list(minishell->list_cmd);
		minishell->list_cmd = NULL;
	}
	free(minishell);
	exit(0);
}