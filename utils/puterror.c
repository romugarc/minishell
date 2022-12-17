/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:22:28 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 20:28:32 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mall_error(void)
{
	g_errno = 134;
	return (-1);
}

int	put_char_error(char c, int mod, int ret)
{
	if (mod == 1)
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		g_errno = 1;
	}
	return (ret);
}

int	puterror_next_mod(char *s1, int mod, int ret)
{
	if (mod == 4)
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putstr_fd(s1, 2);
		ft_putstr_fd("\n", 2);
		g_errno = 1;
	}
	else if (mod == 5)
	{
		g_errno = 127;
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (mod == 6)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	return (ret);
}

int	puterror(char *s1, char *s2, int mod, int ret)
{
	if (mod >= 0 && mod <= 3)
		ft_putstr_fd("minishell: ", 2);
	if (mod == 1)
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (mod == 2)
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_errno = 127;
	}
	else if (mod == 3)
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(s2, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
		return (puterror_next_mod(s1, mod, ret));
	return (ret);
}
