#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

// Global variable for signal handling 
extern int g_signum;

// Signal handling functions
void	handle_signals(int signum);
void	handle_signals_heredoc(int signum);
void	setup_signals_interactive(void);
void	setup_signals_heredoc(void);
void	setup_signals_non_interactive(void);
void	setup_signals_default(void);


#endif
