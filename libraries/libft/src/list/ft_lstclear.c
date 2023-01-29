/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:20:19 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/05 18:40:13 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*to_free;
	t_list	*seek;

	if (!del)
		return ;
	seek = *lst;
	while (seek)
	{
		to_free = seek;
		seek = seek->next;
		ft_lstdelone(to_free, del);
	}
	*lst = 0;
}
