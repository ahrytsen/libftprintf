/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:56:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/18 16:03:07 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getsize(size_t value, int base)
{
	int	res;

	res = 0;
	while (value >= base)
	{
		value /= base;
		res++;
	}
	return (res);
}

char		*ft_ultoa_base(long value, int base, char st_l, char is_unsigned)
{
	size_t	val;
	int		size;
	char	*res;

	size = (!is_unsigned && value < 0 && base == 10) ? 3 : 2;
	val = !is_unsigned && value < 0 && base == 10
		? (size_t)(value * -1) : (size_t)value;
	size += ft_getsize(val, base);
	if (!(res = (char*)malloc(sizeof(char) * size--)))
		return (NULL);
	res[size--] = 0;
	if (!is_unsigned && base == 10 && value < 0)
		res[0] = '-';
	while (val >= (size_t)base)
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
