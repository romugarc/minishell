/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:37:10 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 15:30:36 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*varstr(char **envp, int line)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * strlen_until(envp[line], "=") + 1);
	if (!var)
	{
		g_errno = 134;
		exit(EXIT_FAILURE);
	}
	while (envp[line][i] && envp[line][i] != '=')
	{
		var[i] = envp[line][i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*valuestr(char **envp, int line)
{
	int		i;
	int		v;
	char	*value;

	i = 0;
	v = 0;
	value = malloc(sizeof(char) * strlen_from(envp[line], "=") + 1);
	if (!value)
	{
		g_errno = 134;
		exit(EXIT_FAILURE);
	}
	while (envp[line][i] != '=' && envp[line][i])
		i++;
	if (envp[line][i] == '=')
		i++;
	while (envp[line][i])
	{
		value[v] = envp[line][i];
		i++;
		v++;
	}
	value[v] = '\0';
	return (value);
}
