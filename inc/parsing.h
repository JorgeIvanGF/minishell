/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:26:25 by jorgutie          #+#    #+#             */
/*   Updated: 2025/02/17 11:03:31 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_C
# define PARSING_C

#include "minishell.h"

// Token types___________________________
typedef enum e_token_type
{
	WORD,		// Normal words
	PIPE,		// "|"
	REDIR_IN,	// "<"
	REDIR_OUT,	// ">"
	APPEND,		// ">>"
	HEREDOC		// "<<"
}   t_token_type;

// Token Struct__________________________
typedef struct s_token
{
	char			*value;
	t_token_type 	type;
	struct s_token 	*next;
}   t_token;

// Token List Struct_____________________
typedef struct s_token_list
{
    t_token *head;
    t_token *tail;
    int     size;
}   t_lst_token;

#endif