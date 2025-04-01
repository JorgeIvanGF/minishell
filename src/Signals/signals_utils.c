/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:52:23 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 01:40:50 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signals.h>

void	ft_init_signls_terminal(void)
{
	struct termios	new_term;

	if (tcgetattr(STDIN_FILENO, &new_term) == -1)
		return ;
	new_term.c_lflag &= ~(ECHOCTL);
	new_term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

// Save or restore terminal settings.
// @i: If 0, save the current terminal settings; if non-zero, 
// restore the saved settings.
void	ft_save_restore_terminal(int i)
{
	static struct termios	saved;

	if (!i)
		tcgetattr(STDIN_FILENO, &saved);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}

// Re-enable Ctrl-\ (SIGQUIT) in child processes like cat, grep, etc.
void	enable_sigquit_in_child(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_cc[VQUIT] = 28;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// To print the  ^C  and  ^\Quit: 3
void	print_signal_message(int signal)
{
	if (signal == SIGINT)
		write(STDOUT_FILENO, "^C\n", 3);
	else if (signal == SIGQUIT)
		write(STDOUT_FILENO, "^\\Quit: 3\n", 10);
}
