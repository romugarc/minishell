/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_retnum.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:10:00 by rgarcia           #+#    #+#             */
/*   Updated: 2021/12/15 15:11:24 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_retnum(char *str)
{
	int	i;
	int	printed;

	i = 0;
	printed = 0;
	if (!str)
		return (ft_putstr_retnum("(null)"));
	while (str[i])
	{
		printed += ft_putchar_retnum(str[i]);
		i++;
	}
	return (printed);
}
