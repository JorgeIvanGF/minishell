/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:49:00 by jorgutie          #+#    #+#             */
/*   Updated: 2025/04/03 20:15:23 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parsing.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

// execution helper
char	*get_path(char **env);
char	**get_paths_cmds(char *str);
char	*check_paths_w_cmd(char **path_cmds, char *cmd);
char	*find_path(char **path_cmds, char *cmd);
int		execute(char *found_path, t_cmd *cmd, char **env);
void	iterate_and_execute_cmd_list(t_minishell *minishell);
void	handle_wait_and_exit_status(t_minishell *minishell, int id,
			int *status);
int		process_full_cmd_line(t_cmd *cmd, t_minishell *minishell);
void	execute_cmd_or_builtin_wpipe(t_cmd *cmd, t_minishell *minishell);
void	execute_builtin_without_pipe(t_cmd *cmd, t_minishell *minishell);
void	restore_io(t_minishell *minishell);
void	save_io_fds(t_minishell *minishell);

// built ins
int		is_builtin(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd, t_minishell *minishell);
int		execute_exit(t_cmd *cmd, t_minishell *minishell);
int		execute_pwd(void);
int		execute_unset(char **env, t_cmd *cmd);
int		execute_cd(t_cmd *cmd);
int		execute_echo(t_cmd *cmd);
int		execute_env(char **env, t_cmd *cmd);
int		execute_export(char ***env, t_cmd *cmd);

// built in: export [utils]
int		is_valid_identifier(const char *str);
void	append_new_var(char ***env, const char *var, int count);
void	update_env(char ***env, const char *var);
void	free_env_copy(char **env_copy);

// built in: exit [utils]
void	check_null(t_cmd *cmd, t_minishell *minishell);
void	check_empty(t_cmd *cmd, t_minishell *minishell);
void	check_non_numeric(t_cmd *cmd, t_minishell *minishell);
int		check_too_many_arguments(t_cmd *cmd, t_minishell *minishell);

// redirections
int		setup_redirections(t_cmd *cmd, t_minishell *minishell);
void	redirect_stdout_to_file(int fd_outfile);
void	redirect_stdin_to_file(int fd_infile);
int		handle_heredoc(t_rdir *hdoc_rdir, char *delimiter,
			t_minishell *minishell, int hdoc_counter);
void	check_and_setup_redirections(t_cmd *cmd, t_minishell *minishell);
int		check_heredoc(t_minishell *minishell);
void	unlink_hdoc_files(t_lst_cmd *list_cmd);

// redirections open file
int		open_file_check_rdin(char *rdir_name, int *fd_infile);
char	*open_file_check_rdhoc_wr(int *fd_heredoc_file, int hdoc_counter);
int		open_file_check_rdout(char *rdir_name, int *fd_outfile);
int		open_file_check_rdapnd(char *rdir_name, int *fd_outfile);

// pipe
int		has_pipe(t_cmd *cmd);
void	handle_pipe_redirection(t_cmd *cmd, int fd[2], int process_type);
void	redirect_output_to_pipe(t_cmd *cmd, int fd[2]);
void	redirect_input_to_pipe(int fd[2]);

// printing structs
void	print_redirection(t_rdir *redirection);
void	print_list_redirection(t_lst_rdir *list_redirection);
void	print_cmd_array(char **cmd_arr);
void	print_command(t_cmd *cmd);
void	print_list_commands(t_lst_cmd *list_cmds);

// error
void	error_arguments_exceeded(t_minishell *minishell);
void	error_no_file_directory(char *rdir_name);
void	error_no_numeric_argument(char *cmd_name, t_minishell *minishell);
void	error_cmd_not_found(char *cmd_name);
void	error_env_no_file_directory(char *arg2);
void	error_heredoc(void);

#endif