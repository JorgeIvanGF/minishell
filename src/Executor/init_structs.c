#include "../../inc/minishell.h"
#include "execution.h"

t_lst_rdir *init_list_redirection(t_rdir *head, t_rdir *tail, int size) // TODO: delete or comment all
{
	t_lst_rdir *list_redirection;
	
	list_redirection = malloc(1 * sizeof(t_lst_rdir));
	if (!list_redirection)
	{
		return (NULL);
	}
	list_redirection->head = head;
	list_redirection->tail = tail;
	list_redirection->size = size;

	return(list_redirection);
}

t_rdir *init_redirection(int type, char *name)
{
	t_rdir *redirection; // objekt bzw. instance

	redirection = malloc(1 * sizeof (t_rdir));
	if (!redirection)
	{
		return(NULL);
	}
	redirection->type = type;
	redirection->name = name;
	redirection->next = NULL;

	return(redirection);
}

t_cmd *init_command(char **cmd_arr, t_lst_rdir *list_rdir)
{
	t_cmd *cmd;

	cmd = malloc(1 * sizeof(t_cmd));
	if (!cmd)
	{
		return (NULL);
	}
	cmd->cmd_arr = cmd_arr; 
	cmd->list_rdir = list_rdir;
	cmd->next = NULL;
	return(cmd);
}

t_lst_cmd *init_list_commands(int size, t_cmd *head, t_cmd *tail)
{
	t_lst_cmd *list_cmds;

	list_cmds = malloc(1 * sizeof(list_cmds));
	if (!list_cmds)
	{
		return (NULL);
	}
	list_cmds->size = size;
	list_cmds->head = head;
	list_cmds->tail = tail;

	return (list_cmds);
}

char **init_cmd_array(char *str)
{
	char **cmd_arr;

	cmd_arr = ft_split(str, ' ');

	return(cmd_arr);
}
