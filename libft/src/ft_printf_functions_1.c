/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:07:06 by jorgutie          #+#    #+#             */
/*   Updated: 2024/11/29 22:51:09 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	int	result;

	result = write(1, &c, 1);
	if (result == -1)
		return (-1);
	return (1);
}

int	ft_printstring(char *str)
{
	int	count;
	int	result;

	count = 0;
	if (!str)
		str = "(null)";
	while (*str)
	{
		result = write(1, str, 1);
		if (result == -1)
			return (-1);
		count++;
		str++;
	}
	return (count);
}

int	ft_printdigit(long n)
{
	int		count;
	int		temp;

	count = 0;
	if (n == LONG_MIN)
		return (ft_printstring("-9223372036854775808"));
	if (n < 0)
	{
		if ((ft_printchar('-')) == -1)
			return (-1);
		n = -n;
		count = 1;
	}
	if (n > 9)
	{
		temp = ft_printdigit(n / 10);
		if (temp == -1)
			return (-1);
		count += temp;
	}
	if (ft_printchar((n % 10) + '0') == -1)
		return (-1);
	return (count + 1);
}

int	ft_printhex(long unsigned n, int c)
{
	int		count;
	char	*symbols_l;
	char	*symbols_up;

	count = 0;
	symbols_l = "0123456789abcdef";
	symbols_up = "0123456789ABCDEF";
	if (n < 16)
	{
		if (c == 0)
			return (ft_printchar(symbols_l[n]));
		else
			return (ft_printchar(symbols_up[n]));
	}
	count = ft_printhex(n / 16, c);
	if (count == -1)
		return (-1);
	return (count + ft_printhex((n % 16), c));
}

int	ft_printpointer(void *ptr)
{
	int	count;
	int	check;

	count = 0;
	check = ft_printstring("0x");
	if (check == -1)
		return (-1);
	count += check;
	check = ft_printhex((long unsigned) ptr, 0);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}

// int main (void)
// {
// 	int n = -10;
// 	int r;

// 	r = ft_printhex((unsigned)n,0);
// 	printf("\n%x \n%d", n, r);
// }