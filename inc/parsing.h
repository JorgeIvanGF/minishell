

#ifndef PARSING_C
# define PARSING_C

#include "minishell.h"

// Enum Token types___________________________
typedef enum e_token_type
{
	WORD,		// Normal words
	PIPE,		// "|"
	REDIR_IN,	// "<"
	REDIR_OUT,	// ">"
	APPEND,		// ">>"
	HEREDOC,	// "<<"
	SPACE_		// To temporarily store spaces
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
int			syntax_check(char *input);

// tokenize_helper.c:
void			skip_spaces(const char *input, int *i);
t_token_type	get_token_type(char *word);
t_token			*new_token(char *value, t_token_type type);

#endif