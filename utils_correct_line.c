/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_correct_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:34:27 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/26 16:39:35 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*correct_line(char *line)
{
	int		i;
	char	*correct;

	correct = line;
	i = 0;
	while (correct[i] != '\n')
		i++;
	correct[i] = '\0';
	return (correct);
}
