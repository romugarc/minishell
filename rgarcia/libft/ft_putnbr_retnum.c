/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_retnum.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:10:08 by rgarcia           #+#    #+#             */
/*   Updated: 2021/12/15 15:19:37 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pnbr_l(unsigned long long n, char p, unsigned long long b_l, char *b)
{
	int				printed;

	printed = 0;
	if (n >= b_l)
		printed += ft_pnbr_l(n / b_l, p, b_l, b);
	printed += ft_putchar_retnum(b[n % b_l]);
	return (printed);
}

int	ft_putnbr_retnum(int n, char param, int base_len, char *base)
{
	int				printed;
	int				nflag;
	unsigned int	i;

	printed = 0;
	nflag = 0;
	if (n < 0 && param != 'p')
	{
		if (param == 'u' || param == 'x' || param == 'X')
			i = 4294967296 + n;
		else
		{
			nflag += ft_putchar_retnum('-');
			i = n * -1;
		}
	}
	else
		i = n;
	if (i >= (unsigned int)base_len)
		printed += ft_putnbr_retnum(i / base_len, param, base_len, base);
	printed += ft_putchar_retnum(base[i % base_len]);
	return (printed + nflag);
}
