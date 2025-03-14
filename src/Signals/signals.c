#include <minishell.h>
#include <signals.h>

int g_signum;

void	handle_signals(int signum)
{
	g_signum = signum;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals_heredoc(int signum)
{
	g_signum = signum;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		rl_on_new_line();
	}
}

void	setup_signals_interactive(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	g_signum = 0;
	
	// Setup for SIGINT (Ctrl+C)
	sa_int.sa_handler = handle_signals;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	
	// Setup for SIGQUIT (Ctrl+\) - explicitly ignore
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	g_signum = 0;
	sa.sa_handler = handle_signals_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals_non_interactive(void)
{
	struct sigaction	sa;

	g_signum = 0;
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals_default(void)
{
	struct sigaction	sa;

	g_signum = 0;
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}



