

#ifndef PARSING_C
# define PARSING_C

#include "minishell.h"

// Enum Token types___________________________
typedef enum e_token_type
{
	REDIR_IN,	// "<"
	REDIR_OUT,	// ">"
	APPEND,		// ">>"
	HEREDOC,	// "<<"
	PIPE,		// "|"
	WORD		// Normal words
}	t_token_type;

// Token Struct______________________________
typedef struct s_token
{
	char			*value;
	t_token_type 	type;
	struct s_token 	*next;
}	t_token;

// Token List Struct_________________________
typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
	int		size;
}	t_lst_token;

// Function Prototypes_______________________

// tokenizer.c:
t_lst_token	*tokenize(char *input);
void		free_token_list(t_lst_token *tokens);
void		parser(t_lst_token *tokens, t_minishell *shell);
int			syntax_check(t_lst_token *tokens);

// tokenize_utils.c:
void			skip_spaces(const char *input, int *i);
t_token_type	get_token_type(char *word);
t_token			*new_token(char *value, t_token_type type);
char			*extract_operator(int *i, char *input);
char			*extract_word(int *i, char *input);

// parser.c
void	parser(t_lst_token *tokens, t_minishell *minishell);

#endif