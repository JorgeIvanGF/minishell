/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:13:35 by jorgutie          #+#    #+#             */
/*   Updated: 2025/02/14 00:18:22 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *input;
	t_minishell *minishell;

	
	while (1)
	{
		minishell = init_minishell(env);
		input = readline(ORANGE"MINISHELL> "RESET); // Display prompt and get input
		if (!input) // If Ctrl+D is pressed, exit
		{
			printf("exit\n");
			break;
		}
		if (*input) // If input is not empty, add it to history
			add_history(input);
		printf("--readline: %s\n", input); // to test the readline
		if(!syntax_check(input))
			process_input(input);
		parser(input, minishell);

		//........... Execution Part......................
		ft_execution(minishell); // To Paula
		
		// ............Free Everything....................
		free(input); // Free memory allocated by readline
	}
	return 0;
}