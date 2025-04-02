/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:50:52 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/03 01:09:27 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"
#include "signals.h"

// open file check RD_IN
int	open_file_check_rdin(char *rdir_name, int *fd_infile)
{
	*fd_infile = open(rdir_name, O_RDONLY);
	if (*fd_infile == -1)
	{
		error_no_file_directory(rdir_name);
		return (-1);
	}
	return (1);
}

// open file check RD_HOC 1
// opens or creates file in write mode (truncating if it exists);
char	*open_file_check_rdhoc_wr(int *fd_heredoc_file, int hdoc_counter)
{
	char *file_no;
	char *file_name;

	file_no = ft_itoa(hdoc_counter);
	file_name = ft_strjoin("./src/Executor/redirections/hd_file", file_no);
	*fd_heredoc_file = open(file_name,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file_no);
	if (*fd_heredoc_file == -1)
	{
		error_heredoc();
		return (NULL);
	}
	
	return (file_name);
}

// open file check RD_OUT
int	open_file_check_rdout(char *rdir_name, int *fd_outfile)
{
	*fd_outfile = open(rdir_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_outfile == -1)
	{
		error_no_file_directory(rdir_name);
		return (-1);
	}
	return (1);
}

// open file check RD_APND
int	open_file_check_rdapnd(char *rdir_name, int *fd_outfile)
{
	*fd_outfile = open(rdir_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_outfile == -1)
	{
		error_no_file_directory(rdir_name);
		return (-1);
	}
	return (1);
}
