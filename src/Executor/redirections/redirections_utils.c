/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:50:59 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:51:00 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

void	redirect_stdin_to_file(int fd_infile)
{
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
}

void	redirect_stdout_to_file(int fd_outfile)
{
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
}
