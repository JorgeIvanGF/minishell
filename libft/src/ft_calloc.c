/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:35:00 by jorgutie          #+#    #+#             */
/*   Updated: 2024/10/13 14:20:58 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			tot_size;

	tot_size = count * size;
	ptr = malloc(tot_size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < (tot_size))
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

// int	main(void)
// {
// 	size_t count = 5;
// 	size_t size = sizeof(int);
// 	int *real_mem;
// 	int *custom_mem;

// 	// Testing the real calloc function
// 	real_mem = (int *)calloc(count, size);
// 	if (!real_mem)
// 	{
// 		printf("Failed to allocate memory with real calloc\n");
// 		return (1);
// 	}

// 	// Testing the custom ft_calloc function
// 	custom_mem = (int *)ft_calloc(count, size);
// 	if (!custom_mem)
// 	{
// 		printf("Failed to allocate memory with ft_calloc\n");
// 		free(real_mem);
// 		return (1);
// 	}

// 	// Print results of real calloc
// 	printf("Real calloc memory content:\n");
// 	for (size_t i = 0; i < count; i++)
// 		printf("real_mem[%zu] = %d\n", i, real_mem[i]);

// 	// Print results of custom ft_calloc
// 	printf("\nCustom ft_calloc memory content:\n");
// 	for (size_t i = 0; i < count; i++)
// 		printf("custom_mem[%zu] = %d\n", i, custom_mem[i]);

// 	// Free allocated memory
// 	free(real_mem);
// 	free(custom_mem);

// 	return (0);
// }