/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:40:18 by jorgutie          #+#    #+#             */
/*   Updated: 2024/12/31 13:31:11 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	count_movs;

	count_movs = 0;
	while (*str)
	{
		count_movs++;
		str++;
	}
	return (count_movs);
}
/*
int main(void)
{
	int	r;
	char str[] = "Holas mi querida";
	char* p = str;
	
	r = ft_strlen(p);
	printf("%d", r);
}	*/
