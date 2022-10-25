/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:27:31 by rgarcia           #+#    #+#             */
/*   Updated: 2021/11/23 11:13:02 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*cpy;

	if (!lst)
		return (0);
	i = 0;
	cpy = lst;
	while (cpy)
	{
		cpy = cpy->next;
		i++;
	}
	return (i);
}
