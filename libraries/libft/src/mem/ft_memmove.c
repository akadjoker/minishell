/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:20:43 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/02/15 19:24:52 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (src == dst || len == 0)
		return (dst);
	i = 0;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		i = len;
		while (i-- > 0)
			*(char *)(dst + i) = *(char *)(src + i);
	}
	return (dst);
}
