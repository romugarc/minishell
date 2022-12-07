/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:01:24 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/06 19:30:40 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static int	search_expand(char **line, t_envlist *envc)
{
	t_inc	i;
	t_f_str	f_str;
	t_envlist	*tmp;
	char	*ex_var;
	char	*bef_ex;
	char	*aft_ex;
	char	*tmp_line;
	char	*new_line;

	tmp = envc;
	init_inc(&i);
	quotes_flags(&f_str, *line);
	special_char_flags(&f_str, *line);
	new_line = NULL;
	printf("%s\n", *line);
	while (line[i.i] != '\0')
	{
		i.n = is_in_quotes(f_str, i.i);
		if (*line[i.i] == '$' && i.n != 1)
		{
			printf("%c\n", *line[i.i]);
			i.start = i.i;
			i.l_e = i.start;
			while (*line[i.l_e] != ' ' && is_in_quotes(f_str, i.i) == i.n \
					&& ft_isalpha(*line[i.l_e]) != 0 && line[i.l_e] != '\0')
			{
				i.l_e++;
				i.i++;
			}
			//if (i.l_e == i.start + 1) ne pas faire lignes suivantes
			ex_var = ft_strdup_s_to_e(*line, i.start + 1, i.l_e - 1);
			if (ex_var == NULL)
				return (1);
			while (tmp != NULL && i.l_j == 0)
			{
				if (ft_strrcmp(ex_var, tmp->var) == 0)
					i.l_j = 1;
				else
					tmp = tmp->next;
			}
			if (i.l_j == 1)
			{
				printf("heh\n");
				bef_ex = ft_strdup_s_to_e(*line, i.l_i, i.start);
				if (bef_ex == NULL)
					return (1);
				aft_ex = ft_strdup_s_to_e(*line, i.l_e, ft_strlen(*line));
				if (aft_ex == NULL)
					return (1); //en cas d'erreur de malloc, penser a free ce qui a été malloc avant dans cette fonction
				if (new_line != NULL)
					new_line = ft_strjoin(new_line, bef_ex);
				else
					new_line = ft_strdup(bef_ex);
				if (new_line == NULL)
					return (1);
				tmp_line = new_line;
				new_line = ft_strjoin(new_line, envc->val);
				if (new_line == NULL)
					return (1);
				free(tmp_line);
				tmp_line = new_line;
				new_line = ft_strjoin(new_line, aft_ex);
				if (*line == NULL)
					return (1);
				free(tmp_line);
				free(bef_ex);
				free(aft_ex);
			}
			i.l_i = i.l_e;
			free(ex_var);
		}
		i.i++;
	}
	if (new_line != NULL)
	{
		tmp_line = *line;
		*line = new_line;
		free(tmp_line);
	}
	printf("%s\n", *line);
	printf("%s\n", new_line);
	free(f_str.quotes);
	free(f_str.sp_chars);
	return (0);
}

int expand_variable(t_commands **cmd, int np, t_envlist *envc)
{
	t_inc	i;

	init_inc(&i);
	while (i.i < np)
	{
		i.j = 0;
		while ((*cmd)[i.i].sgl_cmd[i.j] != NULL)
		{
			if (search_expand(&(*cmd)[i.i].sgl_cmd[i.j], envc) == 1)
				return (1);
			i.j++;
		}
		i.i++;
	}
	return (0);
}
