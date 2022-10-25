/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <rgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:57:33 by rgarcia           #+#    #+#             */
/*   Updated: 2022/03/11 17:14:04 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_params_retnum(va_list args, char format)
{
	if (format == 'c')
		return (ft_putchar_retnum(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr_retnum(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_putstr_retnum("0x") + ft_pnbr_l(va_arg(args
					, unsigned long long), format, 16, "0123456789abcdef"));
	else if (format == 'd' || format == 'i' || format == 'u')
		return (ft_putnbr_retnum(va_arg(args, int), format, 10, "0123456789"));
	else if (format == 'x')
		return (ft_putnbr_retnum(va_arg(args
					, int), format, 16, "0123456789abcdef"));
	else if (format == 'X')
		return (ft_putnbr_retnum(va_arg(args
					, int), format, 16, "0123456789ABCDEF"));
	else if (format == '%')
		return (ft_putchar_retnum('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	int				i;
	int				prints;

	va_start(args, format);
	i = 0;
	prints = 0;
	while (format[i])
	{
		if (format[i] != '%')
			prints += ft_putchar_retnum(format[i]);
		else
			prints += ft_params_retnum(args, format[++i]);
		if (format[i] != '\0')
			i++;
	}
	va_end(args);
	return (prints);
}
