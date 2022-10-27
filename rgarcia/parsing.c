/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/27 15:34:57 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_commands **commands, int *nb_pipes, char **line)
{
	*line = get_next_line(0);
	*line = correct_line(*line);
	*nb_pipes = count_arguments(*line, '|');
	*commands = init_commands(*line, *nb_pipes);
	return (0);
}
