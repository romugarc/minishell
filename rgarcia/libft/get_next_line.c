/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:35:10 by rgarcia           #+#    #+#             */
/*   Updated: 2022/03/17 16:43:23 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_find_newline(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] && i < BUFFER_SIZE)
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (BUFFER_SIZE);
}

static int	ft_bufcpy_from_i(char *buff, int index, int max_len)
{
	int	n;
	int	eof;

	n = 0;
	eof = 0;
	while (buff[index] && n < max_len && index < BUFFER_SIZE)
	{
		buff[n] = buff[index];
		n++;
		index++;
		eof++;
	}
	while (buff[n] && n < BUFFER_SIZE)
	{
		buff[n] = '\0';
		n++;
	}
	return (eof);
}

static int	gnl_init(char *gnl, int fd)
{
	int	eof;

	eof = 0;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (-1);
	if (gnl[0] == '\0')
		eof = read(fd, gnl, BUFFER_SIZE);
	else
	{
		while (gnl[eof])
			eof++;
	}
	return (eof);
}

static int	manage_buffer(char *buff, int *flag, int fd)
{
	int	eof;

	eof = read(fd, buff, BUFFER_SIZE);
	if (eof == 0)
		*flag = 1;
	else if (eof < BUFFER_SIZE)
		ft_bufcpy_from_i(buff, 0, eof);
	return (eof);
}

char	*get_next_line(int fd)
{
	static char	gnl[OPEN_MAX][BUFFER_SIZE + 1] = {{}};
	t_var		var;

	var.line = NULL;
	var.flag = 0;
	var.eof = gnl_init(gnl[fd], fd);
	while (var.eof > 0 && var.flag != 1)
	{
		var.i = ft_find_newline(gnl[fd]);
		if (var.i == BUFFER_SIZE)
		{
			var.line = ft_strjoin_to_i(var.line, gnl[fd], var.i);
			var.eof = manage_buffer(gnl[fd], &var.flag, fd);
		}
		else if (var.i <= var.eof - 1)
		{
			var.flag = 1;
			var.line = ft_strjoin_to_i(var.line, gnl[fd], var.i);
		}
	}
	if ((var.eof == 0 && var.flag != 1) || var.eof < 0)
		return (NULL);
	var.eof = ft_bufcpy_from_i(gnl[fd], var.i + 1, var.eof - 1);
	return (var.line);
}
