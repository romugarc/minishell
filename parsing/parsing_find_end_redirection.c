/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_find_end_redirection.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:08:51 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/17 16:55:51 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_end_redirection(t_flag_string f_str, int *k)
{
	while (f_str.special_chars[*k] < '5' && f_str.special_chars[*k] != '\0')
		*k += 1;
	return (*k);
}
