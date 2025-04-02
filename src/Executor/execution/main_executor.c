/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:50:42 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/03 01:06:00 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

// Finds heredoc by going through redirections entered with command
int find_heredoc(t_minishell *minishell, t_cmd *cmd, int *hdoc_counter)
{
	t_rdir *current;
	current = cmd->list_rdir->head;
	int		hdoc_ps_exit_code;
	
	hdoc_ps_exit_code = 0;
	while (current != NULL)
	{
		if (current->type == RD_HDOC)
		{
			(*hdoc_counter)++;
			hdoc_ps_exit_code = handle_heredoc(current, current->name, minishell, *hdoc_counter);
		}
		current = current->next;
	}
	return (hdoc_ps_exit_code);
}

// Checks for heredoc redirection for each command by going through list_cmd 
int check_heredoc(t_minishell *minishell)
{
	t_cmd *current;
	int hdoc_counter;
	int		hdoc_ps_exit_code;
	
	hdoc_ps_exit_code = 0;
	hdoc_counter = 0;
	current = minishell->list_cmd->head;
	while (current != NULL)
	{
		hdoc_ps_exit_code = find_heredoc(minishell, current, &hdoc_counter);
		current = current->next;
	}
	if (hdoc_ps_exit_code == 4)
		minishell->exit_code = 1;
	if (hdoc_ps_exit_code == 3)
		minishell->exit_code = 0;
	return(hdoc_ps_exit_code);
}

void unlink_hdoc_files(t_lst_cmd *list_cmd)
{
	t_cmd	*current_cmd;
	t_rdir  *current_rdir;

	current_cmd = list_cmd->head;
	while (current_cmd != NULL)
	{
		current_rdir = current_cmd->list_rdir->head;
	
		while (current_rdir != NULL)
		{
			if (current_rdir->type == RD_HDOC)
			{
				unlink(current_rdir->name);
			}
			current_rdir = current_rdir->next;
		}
		current_cmd = current_cmd->next;
	}
}

// main execution
// for testing purposes: print_list_commands(minishell->list_cmd);
// check_heredoc: 3 or 4 means hdoc was interrupted with signals; 0 success
int	ft_execution(t_minishell *minishell)
{
	save_io_fds(minishell);
	if(check_heredoc(minishell) == 0) // 3 or 4 means hdoc was interrupted with signals; 0 success
		iterate_and_execute_cmd_list(minishell);
	unlink_hdoc_files(minishell->list_cmd);
	restore_io(minishell);
	return (minishell->exit_code);
}
