/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:52:31 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 20:19:26 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include "../inc/signals.h"
#include "execution.h"

// // To Test the Lexer (Tmporary function)
// void	print_tokens(t_lst_token *tokens)
// {
// 	t_token *curr = tokens->head;
// 	printf(YELLOW"TOKEN VALUES AND TYPES\n"RESET);
// 	while (curr)
// 	{
// 		printf("Token: %-10s | Type: %d\n", curr->value, curr->type);
// 		curr = curr->next;
// 	}
// }

// Disables the terminal's echoing of control characters.
// This function retrieves the current terminal settings, 
// clears the ECHOCTL flag (which normally causes control 
// characters like Ctrl-C to be displayed as "^C"),
// and applies the updated settings immediately.
// void	disable_echoctl(void)
// {
// 	struct termios term;

// 	if (tcgetattr(STDIN_FILENO, &term) == -1)
// 		return ;
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

// Process the command loop
void	command_loop(t_minishell *minishell)
{
	char		*input;
	t_lst_token	*tokens;

	while (1)
	{
		setup_interactive_signals();
		input = get_and_validate_input();
		if (input == NULL)
		{
			if (handle_null_input())
				break ;
			continue ;
		}
		if (handle_empty_input(input))
			continue ;
		if (handle_only_spaces(input))
		{
			free(input);
			continue ;
		}
		if (tokenize_input(input, &tokens))
			continue ;
		if (process_inputs(minishell, tokens, input))
			continue ;
	}
}

// The Main function 
int	main(int argc, char **argv, char **env)
{
	static t_minishell	*minishell;

	(void) argc;
	(void) argv;
	init_minishell(&minishell, env);
	ft_init_signls_terminal();
	ft_save_restore_terminal(0);
	command_loop(minishell);
	ft_save_restore_terminal(1);
	exit_shell(minishell);
	return (0);
}
