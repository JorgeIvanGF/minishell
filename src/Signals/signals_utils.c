// #include <minishell.h>
// #include <signals.h>

// int	g_signum;

// void	setup_signals_default(void)
// {
// 	struct sigaction	sa;

// 	g_signum = 0;
// 	sa.sa_handler = SIG_DFL;
// 	sa.sa_flags = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }

// // New function to handle signal termination:
// // Checks if the child process was terminated by a signal (instead of normally)
// // Returns the actual signal number that caused the termination.
// // If the signal that killed the child was SIGINT(ex. when Ctrl C pressed)
// // -> set the global variable g_signum to SIGINT.
// void	handle_signal_termination(int status)
// {
// 	if (WIFSIGNALED(status))
// 	{
// 		if (WTERMSIG(status) == SIGINT)
// 			g_signum = SIGINT;
// 		else if (WTERMSIG(status) == SIGQUIT)
// 		{
// 			g_signum = SIGQUIT;
// 			write(2, "Quit (core dumped)\n", 19);
// 		}
// 	}
// }
