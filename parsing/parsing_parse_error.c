/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parse_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:52:50 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:30:42 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parse_quote_error(t_f_str f_str, int *i)
{
	int	nb;
	int	mode;

	nb = *i + 1;
	mode = is_sp_char(f_str, *i);
	if (mode == 3)
	{
		while (f_str.quotes[nb] == '1')
			nb++;
		if (f_str.sp_chars[nb] != '3')
			return (1);
	}
	else if (mode == 4)
	{
		while (f_str.quotes[nb] == '2')
			nb++;
		if (f_str.sp_chars[nb] != '4')
			return (1);
	}
	if (mode == 3 || mode == 4)
		*i = nb;
	return (0);
}

static int	parse_redirect_error(t_f_str f_str, int i)
{
	int		nb;
	int		ret;
	char	redir;

	ret = is_sp_char(f_str, i);
	redir = ret + '0';
	if (ret == 6 || ret == 7)
	{
		nb = i;
		while (f_str.sp_chars[nb] == redir)
			nb++;
		if (nb - i > 2 || f_str.sp_chars[nb] == '\0')
			return (1);
		nb = i + 1;
		if (f_str.sp_chars[nb] == redir)
			nb++;
		while (is_sp_char(f_str, nb) == 9 && f_str.sp_chars[nb] != '\0')
			nb++;
		if (is_sp_char(f_str, nb) == 6 || is_sp_char(f_str, nb) == 7 \
			|| is_sp_char(f_str, nb) == 5 || f_str.sp_chars[nb] == '\0')
			return (1);
	}
	return (0);
}

static int	parse_pipe_error(t_f_str f_str, int i)
{
	int	nb;

	if (is_sp_char(f_str, i) == 5)
	{
		nb = i;
		while (f_str.sp_chars[nb] == '5')
			nb++;
		if (nb - i > 1 || f_str.sp_chars[nb] == '\0')
			return (1);
		nb = i + 1;
		while (is_sp_char(f_str, nb) == 9 && f_str.sp_chars[nb] != '\0')
			nb++;
		if (is_sp_char(f_str, nb) == 5 || f_str.sp_chars[nb] == '\0')
			return (1);
	}
	return (0);
}

int	parse_error(char *line, t_f_str f_str)
{
	int	i;

	i = 0;
	while (f_str.sp_chars[i] == '9' && f_str.sp_chars[i] != '\0')
		i++;
	if (f_str.sp_chars[i] == '5')
		return (1);
	i = 0;
	while (line[i] != '\0')
	{
		if (parse_pipe_error(f_str, i) == 1)
			return (1);
		else if (parse_redirect_error(f_str, i) == 1)
			return (1);
		else if (parse_quote_error(f_str, &i) == 1)
			return (1);
		i++;
	}
	return (0);
}
