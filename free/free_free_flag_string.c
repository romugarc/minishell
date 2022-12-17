/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_free_flag_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:42:36 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 17:38:11 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_flag_string(t_f_str flag_string)
{
	free(flag_string.sp_chars);
	free(flag_string.quotes);
}
