/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:49:55 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 01:06:39 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"

// echo w option -n
// in case of -n: no newline will be added
int	execute_echo(t_cmd *cmd)
{
	int	i;
	int	newline_check;

	i = 1;
	newline_check = 1;
	if (cmd->cmd_arr[1] != NULL && ft_strcmp(cmd->cmd_arr[1], "-n") == 0)
	{
		newline_check = 0;
		i++;
	}
	while (cmd->cmd_arr[i])
	{
		write(1, cmd->cmd_arr[i], ft_strlen(cmd->cmd_arr[i]));
		if (cmd->cmd_arr[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline_check == 1)
		write(1, "\n", 1);
	return (1);
}
