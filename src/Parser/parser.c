/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:32:15 by jorgutie          #+#    #+#             */
/*   Updated: 2025/02/17 14:27:11 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	ft_copy_env(t_minishell *shell, char **env)
{
	
}

void	init_minishell(t_minishell *shell, char **env)
{
	shell->env = NULL;
	ft_copy_env(shell, env);
}

