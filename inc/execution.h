#ifndef EXECUTION_H
# define EXECUTION_H

#define CHILD_PROCESS 0
#define PARENT_PROCESS 1

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>


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

// redirections
int redirect_stdin(t_cmd *cmd);
int redirect_stdout(t_cmd *cmd);
int redirect_io(t_cmd *cmd);

// pipe
void setup_pipe(int fd[2]);
int has_pipe(t_cmd *cmd);
void handle_pipe_redirection(t_cmd *cmd, int fd[2], int process_type);

// initializing structs
t_lst_rdir *init_list_redirection(t_rdir *head, t_rdir *tail, int size);
t_rdir *init_redirection(int type, char *name);
t_cmd *init_command(char **cmd_arr, t_lst_rdir *list_rdir);
t_lst_cmd *init_list_commands(int size, t_cmd *head, t_cmd *tail);
char **init_cmd_array(char *str);

// printing structs
void print_redirection(t_rdir *redirection);
void print_list_redirection(t_lst_rdir *list_redirection);
void print_cmd_array(char **cmd_arr);
void print_command(t_cmd *cmd);
void print_list_commands(t_lst_cmd *list_cmds);



// typedef struct s_list_cmds
// {
// 	t_cmd *head;
// 	t_cmd *tail;
// 	int size;
// } t_list_cmds;

// typedef struct s_cmd
// {
// 	char **cmd_array;
// 	t_list_redirection *list;
// } t_cmd;

// typedef struct s_redirection
// {
// 	int type;
// 	char *name;
// 	// pointer to next node
// 	struct s_redirection *next;
// } t_redirection;

// // next: initialize
// typedef struct s_list_redirection
// {
// 	t_redirection *head;
// 	t_redirection *tail;
// 	int size;
// } t_list_redirection;


#endif