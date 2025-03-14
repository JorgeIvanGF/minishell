#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

// Global variable to hold the last received signal
extern volatile sig_atomic_t g_last_signal;

// Initializes signal handling.
void	init_signals(void);

// Signal handler function.
void	handle_signal(int signo);

// Resets signal behavior to default in child processes.
void	reset_child_signals(void);

#endif
