/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:17:45 by rgarcia           #+#    #+#             */
/*   Updated: 2021/11/24 16:05:43 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cpy;

	if (!lst || !f)
		return ;
	cpy = lst;
	while (cpy)
	{
		f(cpy->content);
		cpy = cpy->next;
	}
}
