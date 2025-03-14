#include <minishell.h>
#include <signals.h>

volatile sig_atomic_t g_last_signal = 0;

void handle_signal(int signo)
{
	g_last_signal = signo;
	if (signo == SIGINT)
	{
		// For SIGINT (Ctrl-C): print a newline, clear current input and show a new prompt.
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	// SIGQUIT is ignored (so this handler won't be called for it)
} 

void init_signals(void)
{
	struct sigaction sa;

	// Disable echoing control characters (like ^C) so that they are not printed.
	system("stty -echoctl");

	// Setup handler for SIGINT.
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; // Automatically restart interrupted system calls.
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
	}

	// Ignore SIGQUIT (Ctrl-\)
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
	}
}

void reset_child_signals(void)
{
	// Restore default behavior for SIGINT and SIGQUIT in the child process.
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}




