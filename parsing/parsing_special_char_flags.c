/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_special_char_flags.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:49:16 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/17 16:56:02 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	what_special_char(char *str, int i)
{
	if (str[i] == 39)
		return ('3');
	else if (str[i] == '"')
		return ('4');
	else if (str[i] == '|')
		return ('5');
	else if (str[i] == '>')
		return ('6');
	else if (str[i] == '<')
		return ('7');
	else if (str[i] == '$')
		return ('8');
	else if (str[i] == ' ')
		return ('9');
	return ('0');
}

int	special_char_flags(t_flag_string *flag_string, char *line)
{
	int		i;
	char	*special_string;

	special_string = malloc (sizeof(char) * ft_strlen(line) + 1);
	if (!special_string)
	{
		free(special_string);
		return (1);
	}
	i = 0;
	while (line[i] != '\0')
	{
		special_string[i] = what_special_char(line, i);
		i++;
	}
	special_string[i] = '\0';
	flag_string->special_chars = special_string;
	return (0);
}
