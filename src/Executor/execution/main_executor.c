/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:50:42 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/03 20:46:06 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

// main execution
// command execution processed if no errors in check_heredoc:
// - heredocs are replaced with actual input stored in their files
// - else, commands might not get correct input
// for testing purposes: print_list_commands(minishell->list_cmd);
int	ft_execution(t_minishell *minishell)
{
	save_io_fds(minishell);
	if (check_heredoc(minishell) == 0)
		iterate_and_execute_cmd_list(minishell);
	unlink_hdoc_files(minishell->list_cmd);
	restore_io(minishell);
	return (minishell->exit_code);
}
