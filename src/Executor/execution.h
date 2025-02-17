/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:13:21 by pdrettas          #+#    #+#             */
/*   Updated: 2025/02/17 21:07:10 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include <stdlib.h>
#include <stdio.h>

// Execution________________________________________
void ft_execution (t_minishell *minishell); 


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