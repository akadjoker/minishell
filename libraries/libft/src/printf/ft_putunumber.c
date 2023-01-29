/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunumber.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:10:54 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/03/11 19:08:02 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned int n)
{
	int	len;

	len = 0;
	if (n < 10)
		len += ft_putchar('0' + n);
	else
	{
		len += ft_putunbr(n / 10);
		len += ft_putchar('0' + (n % 10));
	}
	return (len);
}
