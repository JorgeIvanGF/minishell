/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:41:48 by pdrettas          #+#    #+#             */
/*   Updated: 2024/11/12 18:31:45 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	uamount_of_digits(unsigned int n)
{
	unsigned int	counter;

	counter = 0;
	if (n <= 0)
		counter++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

void	ustring_conversion(unsigned int n, char *str, int len)
{
	unsigned int	i;

	i = len - 1;
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
	}
	else
	{
		while (n != 0)
		{
			str[i--] = '0' + (n % 10);
			n /= 10;
		}
	}
}

char	*ft_uitoa(unsigned int n)
{
	unsigned int		len;
	char				*result;

	len = uamount_of_digits(n);
	result = (char *)malloc(len +1);
	if (!result)
		return (NULL);
	ustring_conversion(n, result, len);
	return (result);
}
