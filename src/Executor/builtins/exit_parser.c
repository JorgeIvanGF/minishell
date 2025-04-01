/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:50:02 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:50:03 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"

void	check_null(t_cmd *cmd, t_minishell *minishell)
{
	if (!cmd->cmd_arr[1])
	{
		printf("exit\n");
		exit_shell(minishell);
	}
}

void	check_empty(t_cmd *cmd, t_minishell *minishell)
{
	if (cmd->cmd_arr[1] && ft_strlen(cmd->cmd_arr[1]) == 0)
	{
		error_no_numeric_argument(cmd->cmd_arr[1], minishell);
	}
}

void	check_non_numeric(t_cmd *cmd, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (((cmd->cmd_arr[1] && cmd->cmd_arr[1][i] == '-') || (cmd->cmd_arr[1]
			&& cmd->cmd_arr[1][i] == '+')) && cmd->cmd_arr[1][i + 1])
	{
		i++;
	}
	while (cmd->cmd_arr[1] && cmd->cmd_arr[1][i])
	{
		if (!ft_isdigit(cmd->cmd_arr[1][i]))
		{
			error_no_numeric_argument(cmd->cmd_arr[1], minishell);
		}
		i++;
	}
}

int	check_too_many_arguments(t_cmd *cmd, t_minishell *minishell)
{
	if (cmd->cmd_arr[2])
	{
		error_arguments_exceeded(minishell);
		return (0);
	}
	return (1);
}
