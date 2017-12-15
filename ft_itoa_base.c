/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:56:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/15 15:26:06 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getsize(int value, int base)
{
	int	res;

	res = (value < 0 && base == 10) ? 3 : 2;
	while (value >= base || value <= -base)
	{
		value /= base;
		res++;
	}
	return (res);
}

char		*ft_itoa_base(long value, int base, char st_l)
{
	unsigned long	val;
	int				size;
	char			*res;

	val = value < 0 (unsigned)(value * -1) : value;
	size = ft_getsize(value, base);
	if (!(res = (char*)malloc(sizeof(char) * size--)))
		return (NULL);
	res[size--] = 0;
	if (base == 10 && value < 0)
		res[0] = '-';
	val *= val < 0 ? -1 : 1;
	while (val >= base)
	{
		res[size] = (val % base >= 10) ? val % base + st_l - 10 :
			val % base + '0';
		val /= base;
		size--;
	}
	res[size] = (val % base >= 10) ? val % base + st_l - 10 :
		val % base + '0';
	return (res);
}
