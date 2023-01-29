/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:04:20 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/02 23:13:06 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*   The  memmove()  function  copies  n  bytes from memory area src to
	memory area dest. The memory areas may overlap: copying takes place as
    though the bytes in src are first copied into a temporary array that
	does not overlap src or dest, and the bytes are then copied from  the
    temporary array to dest.
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	if ((size_t)dst - (size_t)src < len)
	{
		i = len;
		while (--i < len)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	}
	else
	{
		i = -1;
		while (++i < len)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	}
	return (dst);
}
