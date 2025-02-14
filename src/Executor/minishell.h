/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:13:21 by pdrettas          #+#    #+#             */
/*   Updated: 2025/02/14 02:03:12 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct s_list_cmds
{
	t_cmd *head;
	t_cmd *tail;
	int size;
} t_list_cmds;

typedef struct s_cmd
{
	char **cmd_array;
	t_list_redirection *list;
} t_cmd;

typedef struct s_redirection
{
	int type;
	char *name;
	// pointer to next node
	struct s_redirection *next;
} t_redirection;

// next: initialize
typedef struct s_list_redirection
{
	t_redirection *head;
	t_redirection *tail;
	int size;
} t_list_redirection;


#endif