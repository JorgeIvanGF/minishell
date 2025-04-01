#include <minishell.h>
#include <signals.h>

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

// ==== NEW: Terminal echo config ==== 

void	ft_init_signls_terminal(void)
{
	struct termios	new_term;

	if (tcgetattr(STDIN_FILENO, &new_term) == -1)
		return;
	new_term.c_lflag &= ~(ECHOCTL);             // Hide ^C / ^
	new_term.c_cc[VQUIT] = _POSIX_VDISABLE;     // Disable Ctrl-
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

 // Save or restore terminal settings.
 // @i: If 0, save the current terminal settings; if non-zero, restore the saved settings.
void	ft_save_restore_terminal(int i)
{
	static struct termios	saved;

	if (!i)
		tcgetattr(STDIN_FILENO, &saved);      // Save terminal settings
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &saved); // Restore at exit
}

// Re-enable Ctrl-\ (SIGQUIT) in child processes like cat, grep, etc.
void	enable_SIGQUIT_in_child(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return;

	term.c_cc[VQUIT] = 28; // ASCII for Ctrl-\, usually the default
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