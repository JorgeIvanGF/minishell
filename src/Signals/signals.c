#include <minishell.h>
#include <signals.h>

//int	g_signum;

// void	handle_signals(int signum)
// {
// 	g_signum = signum;
// 	if (signum == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	handle_signals_heredoc(int signum)
// {
// 	g_signum = signum;
// 	if (signum == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		close(STDIN_FILENO);
// 		rl_on_new_line();
// 	}
// }

// // Setup for SIGINT (Ctrl+C)
// // Setup for SIGQUIT (Ctrl+\) - explicitly ignore
// void	setup_signals_interactive(void)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;

// 	g_signum = 0;
// 	sa_int.sa_handler = handle_signals;
// 	sa_int.sa_flags = 0;
// 	sigemptyset(&sa_int.sa_mask);
// 	sigaction(SIGINT, &sa_int, NULL);
// 	sa_quit.sa_handler = SIG_IGN;
// 	sa_quit.sa_flags = 0;
// 	sigemptyset(&sa_quit.sa_mask);
// 	sigaction(SIGQUIT, &sa_quit, NULL);
// }

// void	setup_signals_heredoc(void)
// {
// 	struct sigaction	sa;

// 	g_signum = 0;
// 	sa.sa_handler = handle_signals_heredoc;
// 	sa.sa_flags = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &sa, NULL);
// }

// void	setup_signals_non_interactive(void)
// {
// 	struct sigaction	sa;

// 	g_signum = 0;
// 	sa.sa_handler = SIG_IGN;
// 	sa.sa_flags = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }


// **********************************************************************

// Global variable to track last signal received
// Must be volatile + sig_atomic_t for async-signal safety
volatile sig_atomic_t	g_sig = 0;


// SIGNAL HANDLER: SIGINT (Ctrl-C) in shell prompt
// Prints a newline, clears input, shows prompt again.
void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		g_sig = signo;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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
