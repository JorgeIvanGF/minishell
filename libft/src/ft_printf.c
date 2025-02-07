/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgutie <jorgutie@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:40:03 by jorgutie          #+#    #+#             */
/*   Updated: 2024/11/29 22:50:39 by jorgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_selection(char specifier, va_list args)
{
	if (specifier == '%')
		return (write(1, "%", 1));
	if (specifier == 'c')
		return (ft_printchar(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_printstring(va_arg(args, char *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_printdigit(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_printdigit(va_arg(args, unsigned int)));
	else if (specifier == 'x')
		return (ft_printhex(va_arg(args, unsigned int), 0));
	else if (specifier == 'X')
		return (ft_printhex(va_arg(args, unsigned int), 1));
	else if (specifier == 'p')
		return (ft_printpointer(va_arg(args, void *)));
	else
		return (0);
}

static int	ft_ifmatch(const char *format, va_list args)
{
	int	result;
	int	count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			result = ft_selection(*(++format), args);
			if (result == -1)
				return (-1);
			count = count + result;
		}
		else
		{
			result = write(1, &*format, 1);
			if (result == -1)
				return (-1);
			count = count + result;
		}
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	if (!format)
		return (0);
	count = ft_ifmatch(format, args);
	va_end(args);
	return (count);
}
