/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 20:34:28 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/03/11 19:21:51 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
	{
		len += ft_putchar('-');
		len += ft_putchar('2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb *= -1;
	}
	if (nb < 10)
	{
		len += ft_putchar(nb + 48);
		return (len);
	}
	else
		len += ft_putnbr(nb / 10);
	len += ft_putnbr(nb % 10);
	return (len);
}
