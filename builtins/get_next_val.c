/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_val.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:05:13 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 13:05:52 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_next_val_1(char *new_var, int *i, t_envlist **cpy, char c)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * strlen_from_c(new_var, '=') + 1);
	if (!tmp)
	{
		g_errno = 134;
		return (NULL);
	}
	if (new_var[0] != '\0')
	{
		*i += 1;
		while (new_var[*i] && new_var[*i - 1] != '=')
			*i += 1;
		if (new_var[*i - 1] == '=')
			(*cpy)->equal = 1;
		if (new_var[*i - 1] == '=' && c == '=')
			free((*cpy)->val);
	}
	return (tmp);
}

static int	get_next_val_2(char *tmp, t_envlist **cpy)
{
	char	*tmp2;

	tmp2 = (*cpy)->val;
	(*cpy)->val = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	if (!(*cpy)->val)
		return (-1);
	return (0);
}

int	get_next_val(t_envlist **envc, char *new_var, char c)
{
	int			i;
	int			j;
	char		*tmp;
	t_envlist	*cpy;

	i = 0;
	j = 0;
	cpy = (*envc);
	tmp = get_next_val_1(new_var, &i, &cpy, c);
	if (!tmp)
		return (-1);
	while (new_var[i])
		tmp[j++] = new_var[i++];
	tmp[j] = '\0';
	if (is_equal(new_var) == 1 && c == '=')
	{
		cpy->val = tmp;
		return (0);
	}
	if (get_next_val_2(tmp, &cpy) == -1)
		return (-1);
	return (0);
}
