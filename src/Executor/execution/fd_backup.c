/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_backup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:50:38 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:50:39 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

// Save original file descriptors of STDIN and STDOUT
void	save_io_fds(t_minishell *minishell)
{
	minishell->og_stdin_fd = dup(STDIN_FILENO);
	minishell->og_stdout_fd = dup(STDOUT_FILENO);
}

// Restore STDIN and STDOUT to their original file descriptors
void	restore_io(t_minishell *minishell)
{
	dup2(minishell->og_stdin_fd, STDIN_FILENO);
	close(minishell->og_stdin_fd);
	dup2(minishell->og_stdout_fd, STDOUT_FILENO);
	close(minishell->og_stdout_fd);
}
