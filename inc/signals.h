// #ifndef SIGNALS_H
// # define SIGNALS_H

// // # include <signal.h>
// // # include <stdio.h>
// // # include <stdlib.h>
// // # include <unistd.h>
// // # include <readline/readline.h>
// // # include <readline/history.h>
// // # include <sys/wait.h>
// // # include <stdbool.h>
// // #include <readline/readline.h>
// // #include <readline/history.h>
// // # include <stdio.h>
// // # include <signal.h>
// // # include <termios.h>
// // # include <unistd.h>
// // # include <string.h>
// // # include <time.h>
// // # include <sys/ioctl.h>
// // # include <sys/wait.h>
// // # include <readline/readline.h>
// // # include <readline/history.h>
// // # include <stdbool.h>
// // # include <fcntl.h>
// // # include <stdlib.h>
// // # include <dirent.h>


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
# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>

// typedef _Bool bool;
// #define false 0
// #define true 1

typedef bool	t_bool;

typedef struct s_global_f
{
	int	cmd;
	int	error_n;
	int	heredoc;
	int	s_heredoc;
}	t_global_f;

// void sigint_handler(int sig, siginfo_t *info, void *context);
void 	sigint_handler(int sig);
void 	sigquit_handler(void);
int		handle_termios(t_bool ctl);
void 	init_signals(void);

#endif