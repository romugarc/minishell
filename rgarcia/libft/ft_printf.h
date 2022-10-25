/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <rgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:00:03 by rgarcia           #+#    #+#             */
/*   Updated: 2021/12/15 13:40:46 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putnbr_retnum(int n, char param, int base_len, char *base);
int	ft_pnbr_l(unsigned long long n, char p, unsigned long long b_l, char *b);
int	ft_putchar_retnum(int c);
int	ft_putstr_retnum(char *str);

#endif
