#ifndef EXECUTION_H
# define EXECUTION_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "minishell.h"
#include "parsing.h"

// execution helper 
char	*get_path(char **env);
char	**get_paths_cmds(char *str);
char	*check_paths_w_cmd(char **path_cmds, char *cmd);
char	*find_path(char **path_cmds, char *cmd);
int		execute(char *found_path, t_cmd *cmd, char **env);

// built ins
int is_builtin(t_cmd *cmd);
int execute_builtin(t_cmd *cmd, t_minishell *minishell);
int execute_exit(t_cmd *cmd, t_minishell *minishell);
int execute_pwd();
int execute_unset(char **env, t_cmd *cmd);
int execute_cd(t_cmd *cmd);
void execute_echo(t_cmd *cmd);
int execute_env(char **env, t_cmd *cmd);
int execute_export(char **env, t_cmd *cmd);

// built in: export [utils]
int		is_valid_identifier(const char *str);
void	append_new_var(char ***env, const char *var, int count);
void	update_env(char ***env, const char *var);

// redirections
int redirect_heredoc(char *delimiter);
int redirect_stdin(t_cmd *cmd);
int redirect_stdout(t_cmd *cmd);
int redirect_io(t_cmd *cmd);

// pipe
int has_pipe(t_cmd *cmd);
void handle_pipe_redirection(t_cmd *cmd, int fd[2], int process_type);
void redirect_output_to_pipe(t_cmd *cmd, int fd[2]);
void redirect_input_to_pipe(int fd[2]);

// printing structs
void print_redirection(t_rdir *redirection);
void print_list_redirection(t_lst_rdir *list_redirection);
void print_cmd_array(char **cmd_arr);
void print_command(t_cmd *cmd);
void print_list_commands(t_lst_cmd *list_cmds);

// error
void error_arguments_exceeded(t_minishell *minishell);
void error_no_file_directory(char *rdir_name);
void error_no_numeric_argument(char *cmd_name, t_minishell *minishell);
void error_cmd_not_found(char *cmd_name);
void error_env_no_file_directory(char *arg2);
void error_heredoc();

// initializing structs // TODO: delete
t_lst_rdir *init_list_redirection(t_rdir *head, t_rdir *tail, int size);
t_rdir *init_redirection(int type, char *name);
t_cmd *init_command(char **cmd_arr, t_lst_rdir *list_rdir);
t_lst_cmd *init_list_commands(int size, t_cmd *head, t_cmd *tail);
char **init_cmd_array(char *str);

#endif