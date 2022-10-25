/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:42:15 by rgarcia           #+#    #+#             */
/*   Updated: 2021/11/27 16:19:39 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoan(int n)
{
	int		count;
	long	div;
	char	*str;

	count = 1;
	div = (long)n;
	while (div < 0)
	{
		div = div / 10;
		count++;
	}
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	div = (long)n;
	str[0] = '-';
	str[count] = '\0';
	count--;
	while (div < 0)
	{
		str[count--] = ((div % 10) * -1) + '0';
		div = div / 10;
	}
	return (str);
}

char	*ft_itoap(int n)
{
	int		count;
	long	div;
	char	*str;

	count = 0;
	div = (long)n;
	while (div > 0 || count == 0)
	{
		div = div / 10;
		count++;
	}
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	str[count] = '\0';
	if (count > 0)
		count--;
	while (count >= 0)
	{
		str[count--] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;

	if (n < 0)
		str = ft_itoan(n);
	else
		str = ft_itoap(n);
	return (str);
}
