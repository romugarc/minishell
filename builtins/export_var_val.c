/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_val.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:12:11 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 13:12:39 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*export_valstr(char *new_var)
{
	int		i_str;
	int		i_nv;
	char	*str;

	i_str = 0;
	i_nv = 0;
	str = malloc(sizeof(char) * strlen_after_c(new_var, '=') + 1);
	if (!str)
		return (NULL);
	while (new_var[i_nv] != '\0' && new_var[i_nv] != '=')
		i_nv++;
	if (new_var[i_nv] != '\0')
		i_nv++;
	while (new_var[i_nv] != '\0')
	{
		str[i_str] = new_var[i_nv];
		i_str++;
		i_nv++;
	}
	str[i_str] = '\0';
	return (str);
}

char	*export_varstr(char *new_var, char c)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * strlen_until_c(new_var, c) + 1);
	if (!var)
		return (NULL);
	i = 0;
	while (new_var[i] && new_var[i] != c)
	{
		var[i] = new_var[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}
