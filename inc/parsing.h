#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// Enum Token types___________________________
typedef enum e_token_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	PIPE,
	WORD,
	DBQ,
	SGQ,
	SPC
}	t_token_type;

// Token Struct______________________________
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// Token List Struct_________________________
typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
	int		size;
}	t_lst_token;

// Function Prototypes_____________________________________________________

// inits.c
void			*init_minishell(t_minishell **minishell, char **env);
int				first_checks(char *input);

// tokenizer.c
t_lst_token		*tokenize(char *input);
void			free_token_list(t_lst_token *tokens);
int				add_token_to_list(char *word, t_lst_token *tokens);

// tokenizer_utils.c
void			skip_spaces(const char *input, int *i);
t_token_type	get_token_type(char *word);
t_token			*new_token(char *value, t_token_type type);
char			*extract_operator(int *i, char *input);
char			*extract_word(int *i, char *input);

// tokenizer_utils_2.c
int				process_word(char *word, t_lst_token *tokens);
char			*extract_dq(int *i, char *input);
char			*extract_sq(int *i, char *input);
char			*extract_spc(int *i, char *input);
char			*extractor(int *i, char *input);

// tokenizer_utils_3.c
char			*extract_quoted(int *i, char *input, char quote);
char			*extract_unquoted(int *i, char *input);
char			*extract_redir_filename(int *i, char *input);
int				process_operator(char *input, int *i, t_lst_token *tokens);
int				process_standard_token(char *input, int *i,
					t_lst_token *tokens);

// tokenizer_utils_4.c
char			*append_segment(char *result, char *segment);

// syntax.c:
int				syntax_check(t_lst_token *tokens, t_minishell *minishell);
void			expand_variables(t_token *token, char **env);

// syntax_uyils_2.c
char			*replace_var(char *input, char *var, char *value, int pos);
void			remove_external_quotes(t_token *token);
char			*extract_var_name(const char *str);

// parser.c
t_lst_cmd		*parser(t_lst_token *tokens, t_minishell *minishell);
void			print_command_list(t_lst_cmd *cmd_list);
void			add_redirection(t_cmd *cmd, t_token *token);
void			add_argument(t_cmd *cmd, char *arg);
void			add_command(t_lst_cmd *cmd_list, t_cmd *cmd);
t_cmd			*new_command(void);

// parser_utils.c
void			print_command_list(t_lst_cmd *cmd_list);
char			*get_redir_name(t_token *token);
int				init_redirection_list(t_cmd *cmd);
int				init_cmd_arr(t_cmd *cmd, char *arg);
char			**expand_cmd_arr(char **old_arr, char *arg);
void			init_lst_cmd(t_minishell *minishell);

// parser_utils_2.c
t_lst_cmd		*finalize_parsing(t_minishell *minishell);
t_token			*skip_spaces_(t_token *token);
t_token			*handle_redirection(t_token *curr, t_cmd *cmd,
					t_minishell *minishell);
t_token			*handle_word_token(t_token *curr, t_cmd *cmd);
t_lst_cmd		*process_tokens(t_token *curr, t_cmd *cmd,
					t_minishell *minishell);

// free.c
void			free_cmd_list(t_lst_cmd *cmd_list);
void			free_token_list(t_lst_token *tokens);
void			free_env(char **env);

// free_2.c
void			continue_shell(t_minishell *minishell,
					t_lst_token **tokens, char **input);
void			exit_shell(t_minishell *minishell);

// main_utils.c
int				process_inputs(t_minishell *minishell,
					t_lst_token *tokens, char *input);
int				tokenize_input(char *input, t_lst_token **tokens);
int				handle_empty_input(char *input);
char			*get_and_validate_input(void);
int				handle_null_input(void);
int				handle_only_spaces(char *input);

// main_utils_2.c
int				handle_null_input(void);

// main.c
void			print_tokens(t_lst_token *tokens);

#endif