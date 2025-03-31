#include <readline/readline.h>
#include <minishell.h>
#include <signals.h>




t_global_f	g_global_var;

void	sigint_handler(int sig)
{
	exit(exit_code_num);
	if (!g_global_var.heredoc)
		ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	sigquit_handler(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&(act.sa_mask));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

int	handle_termios(t_bool ctl)
{
	struct termios	terminos_p;
	int				status;

	(void)ctl;
	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (1);
	terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (1);
	return (0);
}

void	init_signals(void)
{
	// rl_event_hook = NULL;
	handle_termios(true);
	// sigquit_handler();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// void	sigquit_init(void)
// {
// 	struct sigaction	act;

// 	sigquit_handler();
// 	ft_memset(&act, 0, sizeof(struct sigaction));
// 	sigemptyset(&(act.sa_mask));
// 	act.sa_flags = SA_SIGINFO;
// 	act.sa_sigaction = &sigint_handler;
// 	sigaction(SIGINT, &act, NULL);
// 	return ;
// }
// #include <minishell.h>
// #include <signals.h>

// int	g_signum;

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

// TODO: in "MINISHELL> ^Dexit" -> remove ^D (jorge)
