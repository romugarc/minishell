/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/09 17:23:56 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	tab_redirections(t_commands **commands, t_flag_string flag_string, char **line)
{
	
	return (0);
}*/
/*int	split_redirection(char *tab, char **tab_files, int nb_files, t_flag_string f_str)
{
	int	i;
	int	j;

	i = 0;
	(void)f_str;
	while (tab_files[i] != 0)
		i++;
	while (i < nb_files)
	{
		j = 0;
		while (tab[j] != '\0')
		{
			j++;
		}
		i++;
	}
	return (0);
}*/

/*static char	*ft_strdup_s_to_e(char const *src, size_t n, size_t index)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * ((index - n) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[n] && n < index)
	{
		dest[i] = src[n];
		n++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_redirection(t_commands *c, char *str, t_flag_string f_str, int *k)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && f_str.quotes[*k] == '0')
		{
			if (str[i + 1] != '>')
				c->nb_outfile += 1;
		}
		else if (str[i] == '<' && f_str.quotes[*k] == '0')
		{
			if (str[i + 1] != '<')
				c->nb_infile += 1;
		}
		i++;
		*k += 1;;
	}
	return (0);
}

void	count_redirections(t_commands **commands, int np, t_flag_string f_str)
{
	int	i;
	int	j;
	int	k;
	int	r;

	i = -1;
	k = 0;
	while (++i < np)
	{
		(*commands)[i].nb_outfile = 0;
		(*commands)[i].nb_infile = 0;
		j = 0;
		while ((*commands)[i].single_command[j] != 0)
		{
			while ((f_str.special_chars[k] == '5' || \
					f_str.special_chars[k] == '9') && f_str.quotes[k] == '0')
				k++;
			if (f_str.quotes[k] != '\0')
				r = is_redirection(&(*commands)[i], (*commands)[i].single_command[j], f_str, &k);
			j++;
		}
	}
}

int	malloc_tab_files(t_commands **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			(*c)[i].tab_infile = malloc(sizeof(char *) * ((*c)[i].nb_infile + 1));
			if (!(*c)[i].tab_infile)
				return (1);
		}
		if ((*c)[i].nb_outfile > 0)
		{
			(*c)[i].tab_outfile = malloc(sizeof(char *) * ((*c)[i].nb_outfile + 1));
			if (!(*c)[i].tab_outfile)
				return (1);
		}
		i++;
	}
	return (0);
}*/

/*char	*form_tab_2(char c, t_commands *comm, t_flag_string f_str, t_inc *inc)
{
	int		start;
	int		end;
	char	*ret;

	printf("%s\n", f_str.special_chars);
	start = find_special_char(c, f_str, &inc->k);
	while ((f_str.special_chars[inc->k] == c || f_str.special_chars[inc->k] == '9') && f_str.special_chars[inc->k] != '\0')
		inc->k++;
	start = inc->k;
	printf("%d\t%c\n", start, f_str.special_chars[start]);
	end = find_end_redirection(f_str, &inc->k);
	printf("%d\t%c\n", end, f_str.special_chars[end]);
	ret = ft_strdup_s_to_e(comm[inc->i].single_command[inc->j], start, end);
	printf("%s\n", comm[inc->i].single_command[inc->j]);
	printf("%s\n", ret);
	inc->n += 1;
	return (ret);
}*/

/*int	form_tab(t_commands **com, t_flag_string f_str, int np)
{
	t_inc	i;
	int		start;
	int		end;

	i.i = 0;
	i.k = 0;
	i.n = 0;
	i.l_i = 0;
	i.l_j = 0;
	i.l_e = 0;
	while(i.i < np)
	{
		i.j = 0;
		while ((*com)[i.i].single_command[i.j] != 0 && i.n < (*com)[i.i].nb_infile)
		{
			while ((f_str.special_chars[i.k] == '5' \
					|| f_str.special_chars[i.k] == '9') \
					&& f_str.quotes[i.k] == '0')
				i.k += 1;
			printf("%d\t%d\n", com[i.i]->nb_infile, i.n);
			start = find_special_char('7', f_str, &i, (*com)[i.i].single_command[i.j]);
			if (start > -1)
			{
				printf("huh\n");
				if (f_str.special_chars[i.k + 1] == '7')
				{
					i.k += 1;
					start += 1;
				}
				if (f_str.special_chars[i.k + 1] == '9' && f_str.special_chars[i.k + 1] != '\0')
				{
					start = 0;
					end = 0;
					i.j++;
					printf("%s\t%s\n", f_str.special_chars, (*com)[i.i].single_command[i.j]);
					while ((f_str.special_chars[i.k] == '7' || f_str.special_chars[i.k] == '9') && f_str.special_chars[i.k] != '\0')
						i.k++;
					while ((f_str.special_chars[i.k] < '5' || (f_str.special_chars[i.k] == '9' && f_str.quotes[i.k] != '0')) \
						&& f_str.special_chars[i.k] != '\0')
					{
						end += 1;
						i.k++;
					}
					i.l_e = end;
					if ((*com)[i.i].single_command[i.j] != 0)
					{
						(*com)[i.i].tab_infile[i.n] = ft_strdup_s_to_e((*com)[i.i].single_command[i.j], start, end);
						printf("%s\n", (*com)[i.i].tab_infile[i.n]);
						i.n += 1;
					}
				}
				else if (f_str.special_chars[i.k + 1] != '\0')
				{
					end = start + 1;
					i.k += 1;
					while ((f_str.special_chars[i.k] < '5' || (f_str.special_chars[i.k] == '9' && f_str.quotes[i.k] != '0')) \
						&& f_str.special_chars[i.k] != '\0')
					{
						end += 1;
						i.k++;
					}
					i.l_e = end;
					if ((*com)[i.i].single_command[i.j] != 0)
					{
						(*com)[i.i].tab_infile[i.n] = ft_strdup_s_to_e((*com)[i.i].single_command[i.j], start + 1, end);
						printf("%s\n", (*com)[i.i].tab_infile[i.n]);
						i.n += 1;
					}
				}
			}
			if ((*com)[i.i].single_command[i.j] != 0 && (*com)[i.i].single_command[i.j][end] == '\0')
				i.j += 1;
		}
		i.k += 1;
		i.i += 1;
	}
	return (0);
}*/

/*int	correct_tabs(t_commands **c, t_flag_string flag_string, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			form_tab(&(*c)[i], flag_string);
		}
		if ((*c)[i].nb_outfile > 0)
		{
			(*c)[i].tab_outfile = malloc(sizeof(char *) * (*c)[i].nb_outfile);
			if (!(*c)[i].tab_outfile)
				return (1);
		}
		i++;
	}
	return (0);
}*/

int	parsing(t_commands **commands, t_flag_string *flag_string, int *nb_pipes, char **line)
{
	*line = get_next_line(0);
	*line = correct_line(*line);
	if (special_char_flags(flag_string, *line) != 0)
		return (1);
	if (quotes_flags(flag_string, *line) != 0)
		return (1);
	*nb_pipes = count_arguments(*line, '|', *flag_string);
	*commands = init_commands(*line, *nb_pipes, *flag_string);
	count_redirections(commands, *nb_pipes, *flag_string);
	// parcourir commands[i].nb_infiles et outfiles et si ces valeurs sont à 0, on ne fait pas les 2 prochaines lignes
//	malloc_tab_files(commands, *nb_pipes);
//	form_tab(commands, *flag_string, *nb_pipes);
//	correct_tabs(commands, *flag_string, *nb_pipes);
	return (0);
}

//debug code pour commands (attention aux segfault si y a rien dans commands)
/*	i = 0;
	while (i < *nb_pipes)
	{
		printf("avantnb\n");
		commands[i]->nb_infile = 0;
		commands[i]->nb_outfile = 0;
		printf("avantredir\n");
		count_redirections(commands[i], *flag_string, tab);
		printf("%d\t%d\n", commands[i]->nb_infile, commands[i]->nb_outfile);
		i++;
	}*/

