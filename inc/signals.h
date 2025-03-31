// #ifndef SIGNALS_H
// # define SIGNALS_H


// // Global variable for signal handling 
// extern int	g_signum;

// // Signal handling functions_________________
// void	handle_signals(int signum);
// void	handle_signals_heredoc(int signum);
// void	setup_signals_interactive(void);
// void	setup_signals_heredoc(void);
// void	setup_signals_non_interactive(void);
// void	setup_signals_default(void);
// void	handle_signal_termination(int status);


// #endif
#ifndef SIGANALS_H
# define SIGANALS_H

# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <time.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

// Global variable for signal handling 
//extern int	g_signum; //SIGNALS

extern volatile sig_atomic_t	g_sig;

// Signal handling functions_________________
// void	handle_signals(int signum);
// void	handle_signals_heredoc(int signum);
// void	setup_signals_interactive(void);
// void	setup_signals_heredoc(void);
// void	setup_signals_non_interactive(void);
// void	setup_signals_default(void);
// void	handle_signal_termination(int status);

// // New ones
// void	handle_signals_interactive(void);
// void	handle_signals_child(void);
// void	signal_handler(int signo);

// New new
void	handle_sigint(int signo);
void	handle_sigquit(int signo);
void	setup_interactive_signals(void);
void	setup_exec_signals(void);
void	handle_sigint_heredoc(int signo);
void	setup_heredoc_signals(void);


#endif