#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include "../inc/signals.h"
#include "execution.h"

// To Test the Lexer (Tmporary function)
void print_tokens(t_lst_token *tokens)
{
	t_token *curr = tokens->head;
	printf(YELLOW"TOKEN VALUES AND TYPES\n"RESET);
	while (curr)
	{
		printf("Token: %-10s | Type: %d\n", curr->value, curr->type);
		curr = curr->next;
	}
}

// Disables the terminal's echoing of control characters.
// This function retrieves the current terminal settings, 
// clears the ECHOCTL flag (which normally causes control 
// characters like Ctrl-C to be displayed as "^C"),
// and applies the updated settings immediately.
void disable_echoctl(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Process the command loop
void command_loop(t_minishell *minishell)
{
	char *input;
	t_lst_token *tokens;
	
	while (1) // changed by Paula
	{
		input = get_and_validate_input();
		if (input == NULL)
		{
			if (handle_null_input())
				break;
			continue;
		}
		if (handle_empty_input(input))
			continue;
		if (handle_only_spaces(input)) 
		{
			free(input);
			continue;
		}
		if (tokenize_input(input, &tokens))
			continue;
		if (process_inputs(minishell, tokens, input))
			continue;
	}
}



// The Main function 
// int	main(int argc, char **argv, char **env)
// {
// 	t_minishell	*minishell;
	
// 	(void) argc;
// 	(void) argv;
// 	init_minishell(&minishell, env);
// 	disable_echoctl(); // Disable echoing of control characters
// 	// setup_signals_interactive();

// 	command_loop(minishell); // parsing, execution happens here
// 	// printf("exit flag in main = %d\n", minishell->exit_requested); // for testing

// 	exit_shell(minishell); 
// 	// printf("final exit code (in main) = %d\n", exit_code); // for testing

// 	return (0);
// }



// --------------------- HEREDOC ---------------------------------------------
int heredoc(char *delimiter) // TODO: call somewhere else / implement properly
{
	// (void) delimiter;
	int heredoc;
	char *line;

	heredoc = open("viktoria1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc == -1)
	{
		write(2, "minishell: ", 11); // bash
		write(2, "viktoria1", 9);
		write(2, ": No such file or directory\n", 28);
		return (-1);
	}

	delimiter = ft_strjoin(delimiter, "\n"); // bc line has new line
	while (1)
	{
		// printf("> "); //=========> [ '>', ' ' ]
		// printf("\n");
		write (1, "> ", 2);
		line = get_next_line(0);
		if (ft_strcmp(line, delimiter) == 0)
		{
			break;
		}
		write(heredoc, line, ft_strlen(line));
		ft_free(line);
		// printf("delimiter = -%s-\n", delimiter);
		// printf("line = -%s-\n", line);
	}
	ft_free(delimiter);

	close(heredoc);
	unlink("viktoria1");
	
	return (1);
}

int main ()
{
	heredoc("n");

	return (0);
}