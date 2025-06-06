/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:51:17 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 23:42:49 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// Continue with the main loop:
// Free Cmd List (and set to NULL)
// Free Token List (and set to NULL)
// Free the input (and set to NULL)
void	continue_shell(t_minishell *minishell, t_lst_token **tokens,
	char **input)
{
	if (minishell->list_cmd)
	{
		free_cmd_list(minishell->list_cmd);
		minishell->list_cmd = NULL;
	}
	free_token_list((*tokens));
	(*tokens) = NULL;
	free((*input));
	(*input) = NULL;
}

// Free everything before exiting:
// Free Cmd List (and set to NULL)
// Free ENV (and set to NULL)
// Free the MINISHELL itself
void	exit_shell(t_minishell *minishell)
{
	int	exit_code;

	exit_code = minishell->exit_code;
	if (minishell->list_cmd)
	{
		free_cmd_list(minishell->list_cmd);
		minishell->list_cmd = NULL;
	}
	if ((minishell->env))
	{
		free_env(minishell->env);
		minishell->env = NULL;
	}
	if (minishell)
		free(minishell);
	exit(exit_code);
}
