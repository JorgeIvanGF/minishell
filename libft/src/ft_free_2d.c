/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:10:40 by pauladretta       #+#    #+#             */
/*   Updated: 2024/12/28 06:02:55 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d(char **matrix)
{
	int	i;

	if (matrix == NULL)
	{
		return ;
	}
	i = 0;
	while (matrix != NULL && matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	if (matrix != NULL)
	{
		free(matrix);
	}
}
