/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/07 19:23:42 by rgarcia          ###   ########lyon.fr   */
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

static char	*ft_strdup_s_to_e(char const *src, size_t n, size_t index)
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

	printf("%s\n", str);
	i = 0;
	printf("%c\t%d\n", f_str.quotes[*k], *k);
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
			(*c)[i].tab_infile = malloc(sizeof(char *) * (*c)[i].nb_infile);
			if (!(*c)[i].tab_infile)
				return (1);
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
}

int	find_special_char(char c, t_flag_string f_str, int *k)
{
	while (f_str.special_chars[*k] != '\0')
	{
		if (f_str.special_chars[*k] == c && f_str.quotes[*k] == '0')
		{
			if (f_str.special_chars[*k + 1] != c)
				return (*k);
		}
		*k += 1;
	}
	return (*k);
}

int	find_end_redirection(char c, t_flag_string f_str, int *k)
{
	while (f_str.special_chars[*k] == c && f_str.special_chars[*k] != '\0')
		*k += 1;
	while (f_str.special_chars[*k] < '5' && f_str.special_chars[*k] != '9' \
		&& f_str.special_chars[*k] != '\0')
		*k += 1;
	return (*k);
}

char	*form_tab_2(char c, t_commands *comm, t_flag_string f_str, t_inc *inc)
{
	int		start;
	int		end;
	char	*ret;

	start = find_special_char(c, f_str, &inc->k);
	end = find_end_redirection(c, f_str, &inc->k);
	ret = ft_strdup_s_to_e(comm[inc->i].single_command[inc->j], start, end);
	inc->n += 1;
	return (ret);
}

int	form_tab(t_commands *com, t_flag_string f_str, int np)
{
	t_inc	i;

	i.i = 0;
	i.k = 0;
	while(i.i < np)
	{
		i.j = 0;
		while ((com)[i.i].single_command[i.j] != 0)
		{
			while ((f_str.special_chars[i.k] == '5' \
					|| f_str.special_chars[i.k] == '9') \
					&& f_str.quotes[i.k] == '0')
				i.k += 1;
			if (i.n < com[i.i].nb_infile && com[i.i].single_command[i.j] != 0)
				com[i.i].tab_infile[i.n] = form_tab_2('<', com, f_str, &i);
		}
		i.k += 1;
		i.i += 1;
	}
	return (0);
}
//todo: Creer une fonction qui va correctement creer les tableaux dans form tab pour la norme, tester tout ca, 
//organiser toutes les fonctions deja finies dans des fichiers
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
//	char	**tab;
//	char	**tab_infiles;
//	char	**tab_outfiles;
//	int		i;
//	int		j;
//	int		k;
//	int		nb_infiles;
//	int		nb_outfiles;

	*line = get_next_line(0);
	*line = correct_line(*line);
	if (special_char_flags(flag_string, *line) != 0)
		return (1);
	if (quotes_flags(flag_string, *line) != 0)
		return (1);
	*nb_pipes = count_arguments(*line, '|', *flag_string);
//	tab = ft_split_v2(*line, '|', *flag_string);
//	*commands = malloc(sizeof(t_commands) * *nb_pipes);
//	if (!commands)
//		return (0);
/*	tab_infiles = malloc(sizeof(char *) * (nb_infiles + 1));
	if (!tab_infiles)
		return (1);
	tab_outfiles = malloc(sizeof(char *) * (nb_outfiles + 1));
	if (!tab_outfiles)
		return (1);*/
	*commands = init_commands(*line, *nb_pipes, *flag_string);
	count_redirections(commands, *nb_pipes, *flag_string);
	malloc_tab_files(commands, *nb_pipes);
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

