/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:52:27 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/02 01:52:30 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <minishell.h>
#include <signals.h>

// Global variable to track last signal received
// Must be volatile + sig_atomic_t for async-signal safety
volatile sig_atomic_t	g_sig = 0;

// Called only in main shell prompt (readline) //NEW
void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		g_sig = signo;
		if (isatty(STDIN_FILENO))
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

// SETUP: Signals for interactive mode (when waiting for user input)
// - SIGINT (Ctrl-C) prints prompt again
// - SIGQUIT (Ctrl-\) is ignored
void	setup_interactive_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// SETUP: Signals in child process (for commands like execve)
// Restores default behavior so Ctrl-C and Ctrl-\ work normally.
void	setup_exec_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// SIGNAL HANDLER: SIGINT (Ctrl-C) inside heredoc
// Closes STDIN so get_next_line() returns NULL and heredoc is aborted.
void	handle_sigint_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

// SETUP: Signals during heredoc input (<<)
// - SIGINT (Ctrl-C) aborts heredoc
// - SIGQUIT (Ctrl-\) is ignored
void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
