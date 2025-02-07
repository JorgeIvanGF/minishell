/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:44:40 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 14:20:46 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	return ;
}

// int main(void)
// {
// 	char str[30]= "abcd efgh";
// 	ft_bzero(str,3);	
// 	int j = 0;
// 	while(j < 30)  // Change to iterate through the WHOLE buffer
// 	{
// 		printf("%d ", str[j]);  // Print each byte as AN INTEGER
// 		j++;				
// 	}
// 	printf("\n");

// 	return 0;
// }
