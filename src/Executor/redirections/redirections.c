/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:51:04 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:51:05 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

int		setup_redirections(t_cmd *cmd, t_minishell *minishell);
int		handle_input_redirection(t_rdir *current, t_minishell *minishell);
int		handle_output_redirection(t_rdir *current);

// Redirect both STDIN and STDOUT based on the redirection types in the command
void	check_and_setup_redirections(t_cmd *cmd, t_minishell *minishell)
{
	if (setup_redirections(cmd, minishell) == 0)
	{
		minishell->exit_code = 1;
		exit_shell(minishell);
	}
}

// Redirect STDIN & STDOUT from specified file(s) 
// based on the redirection type in cmd
int	setup_redirections(t_cmd *cmd, t_minishell *minishell)
{
	t_rdir	*current;

	if (cmd && cmd->list_rdir && cmd->list_rdir->head)
	{
		current = cmd->list_rdir->head;
		while (current != NULL)
		{
			if (handle_input_redirection(current, minishell) == 0)
			{
				return (0);
			}
			else if (handle_output_redirection(current) == 0)
			{
				return (0);
			}
			current = current->next;
		}
	}
	return (1);
}

// Redirects STDIN by opening specified file (<) or processing a heredoc (<<)
int	handle_input_redirection(t_rdir *current, t_minishell *minishell)
{
	int	fd_file;

	if (current->type == RD_IN)
	{
		if (open_file_check_rdin(current->name, &fd_file) == -1)
			return (0);
		redirect_stdin_to_file(fd_file);
	}
	else if (current->type == RD_HDOC && current->name)
	{
		fd_file = redirect_heredoc(current->name, minishell);
		if (fd_file == -1)
			return (0);
		redirect_stdin_to_file(fd_file);
	}
	return (1);
}

// Redirects STDOUT by opening specified file
// in either truncate (>) or append (>>) mode
int	handle_output_redirection(t_rdir *current)
{
	int	fd_file;

	if (current->type == RD_OUT)
	{
		if (open_file_check_rdout(current->name, &fd_file) == -1)
			return (0);
		redirect_stdout_to_file(fd_file);
	}
	else if (current->type == RD_APND)
	{
		if (open_file_check_rdapnd(current->name, &fd_file) == -1)
			return (0);
		redirect_stdout_to_file(fd_file);
	}
	return (1);
}
