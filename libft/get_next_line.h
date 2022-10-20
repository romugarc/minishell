/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:30:12 by rgarcia           #+#    #+#             */
/*   Updated: 2022/03/11 17:11:37 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

typedef struct t_variables {
	char	*line;
	int		i;
	int		eof;
	int		flag;
}	t_var;

char	*get_next_line(int fd);
char	*get_next_line_bonus(int fd);
char	*ft_strjoin_to_i(char *s1, char *s2, int max_len);

#endif
