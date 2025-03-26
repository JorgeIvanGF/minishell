#include "minishell.h"
#include "parsing.h"

// To free all the tokens in the list, and also the list itself
void	free_token_list(t_lst_token *tokens)
{
	t_token	*curr;
	t_token	*next;

	if (!tokens)
		return ;
	curr = tokens->head;
	while (curr)
	{
		next = curr->next;
		free(curr->value);
		curr->next = NULL;
		free(curr);
		curr = next;
	}
	free(tokens);
}

// Free the list of redirections
void	free_redirections(t_lst_rdir *list_rdir)
{
	t_rdir	*tmp;
	t_rdir	*redir;

	if (!list_rdir)
		return ;
	redir = list_rdir->head;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->name);
		tmp->name = NULL;
		free(tmp);
		tmp = NULL;
	}
	list_rdir->head = NULL;
	free(list_rdir);
}

// Free a single command:
// Free command arguments -> free each argument string -> Setting to NULL
// to Prevent dangling pointers -> Free the array itself
// Setting the array to NULL to Avoid potential double free.
// Free redirections safely and Ensure it’s null after freeing
// Free the command struct->Avoid use after free
void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd_arr)
	{
		while (cmd->cmd_arr[i])
		{
			free(cmd->cmd_arr[i]);
			cmd->cmd_arr[i] = NULL;
			i++;
		}
		free(cmd->cmd_arr);
		cmd->cmd_arr = NULL;
	}
	if (cmd->list_rdir)
	{
		free_redirections(cmd->list_rdir);
		cmd->list_rdir = NULL;
	}
	free(cmd);
	cmd = NULL;
}

// Free the entire command list:
// Free each command->Set to NULL toPrevent accessing 
// freed memory->Free the command list struct
void	free_cmd_list(t_lst_cmd *cmd_list)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	if (!cmd_list)
		return ;
	cmd = cmd_list->head;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_cmd(tmp);
	}
	cmd_list->head = NULL;
	free(cmd_list);
}

// Free duplicated ENV:
// Free each duplicated environment variable
// Free the array itself
void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
