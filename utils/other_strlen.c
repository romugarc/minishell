/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_strlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:28:01 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 13:13:57 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strlen_until(char *str, char *until)
{
	int	i;
	int	u;

	i = 0;
	while (str[i])
	{
		u = 0;
		while (until[u])
		{
			if (str[i] == until[u])
				return (i);
			u++;
		}
		i++;
	}
	return (i);
}

int	strlen_from(char *str, char *from)
{
	int	i;
	int	f;
	int	count;

	i = 0;
	count = -2;
	while (str[i])
	{
		f = 0;
		while (from[f])
			if (str[i] == from[f++] && count == -2)
				count = -1;
		i++;
		if (count >= -1)
			count++;
	}
	if (count == -2)
		return (0);
	return (count);
}

int	strlen_from_c(char *str, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	if (str[i])
		i++;
	while (str[i++])
		size++;
	return (size);
}

int	strlen_after_c(char *new_var, char c)
{
	int	i;
	int	size;

	i = 0;
	while (new_var[i] && new_var[i] != c)
		i++;
	if (new_var[i] != '\0')
		i++;
	size = 0;
	while (new_var[i])
	{
		size++;
		i++;
	}
	return (size);
}

int	strlen_until_c(char *new_var, char c)
{
	int	i;

	i = 0;
	while (new_var[i] && new_var[i] != c)
		i++;
	return (i);
}
