/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_find_end_redirection.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:08:51 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/19 14:48:37 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_end_redirection(t_f_str f_str, int *k)
{
	while (f_str.sp_chars[*k] < '5' && f_str.sp_chars[*k] != '\0')
		*k += 1;
	return (*k);
}
