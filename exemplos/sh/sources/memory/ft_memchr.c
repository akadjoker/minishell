/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 23:12:02 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/02 23:11:21 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The  memchr()  function scans the initial n bytes of the memory area pointed
	to by s for the first instance of c.  Both c and the bytes of
    the memory area pointed to by s are interpreted as unsigned char.*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((char *)s + i) == (char) c)
			return ((void *)s + i);
		i += sizeof(char);
	}
	return (NULL);
}
