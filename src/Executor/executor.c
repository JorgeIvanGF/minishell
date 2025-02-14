/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:02:40 by pdrettas          #+#    #+#             */
/*   Updated: 2025/02/14 02:03:41 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_redirection *init_list_redirection(t_redirection *head, t_redirection *tail, int size)
{
	t_list_redirection *list_redirection;
	
	list_redirection = malloc(1 * sizeof(t_list_redirection));
	if (!list_redirection)
	{
		return (NULL);
	}
	list_redirection->head = head;
	list_redirection->tail = tail;
	list_redirection->size = size;

	return(list_redirection);
}

t_redirection *init_redirection(int type, char *name)
{
	t_redirection *redirection; // objekt bzw. instance

	redirection = malloc(1 * sizeof (t_redirection));
	if (!redirection)
	{
		return(NULL);
	}
	redirection->type = type;
	redirection->name = name;
	redirection->next = NULL;
	return(redirection);
}

int main ()
{
	t_redirection *redirection_0;
	t_redirection *redirection_1;
	t_redirection *redirection_2;
	t_redirection *redirection_3;
	t_list_redirection *list_redirection;
	
	redirection_0 = init_redirection(0, NULL);
	// printf("redirection 0: type = %d, name = %s\n", redirection_0->type, redirection_0->name);
	redirection_1 = init_redirection(1, NULL);
	// printf("redirection 1: type = %d, name = %s\n", redirection_1->type, redirection_1->name);
	redirection_2 = init_redirection(2, NULL);
	// printf("redirection 2: type = %d, name = %s\n", redirection_2->type, redirection_2->name);
	redirection_3 = init_redirection(3, NULL);
	// printf("redirection 3: type = %d, name = %s\n", redirection_3->type, redirection_3->name);
	
	redirection_0->next = redirection_1;
	redirection_1->next = redirection_2;
	redirection_2->next = redirection_3;
	redirection_3->next = NULL;

	list_redirection = init_list_redirection(redirection_0, redirection_3, 4);

	
	return (0);
}
