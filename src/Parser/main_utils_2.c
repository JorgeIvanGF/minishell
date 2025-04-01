/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:51:29 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 00:51:30 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// Handle NULL input (Ctrl+D case):
// Signal to break the main loop
int	handle_null_input(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		return (1);
	return (0);
}
