/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:46:09 by rgarcia           #+#    #+#             */
/*   Updated: 2021/11/24 18:07:48 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cpy;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		cpy = *lst;
		*lst = cpy->next;
		ft_lstdelone(cpy, del);
	}
	*lst = NULL;
}
