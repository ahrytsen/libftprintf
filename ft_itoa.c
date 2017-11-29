/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:53:47 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/01 21:23:28 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countdigits(int n)
{
	int res;

	res = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n /= -10;
		res += 2;
	}
	while (n > 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}

char		*ft_itoa(int n)
{
	char	*a;
	int		len;

	len = ft_countdigits(n);
	if (!(a = ft_strnew(len)))
		return (NULL);
	a[len] = 0;
	len--;
	if (n == 0)
		a[0] = '0';
	if (n < 0)
	{
		a[0] = '-';
		a[len] = (n % 10) * -1 + '0';
		len--;
		n /= -10;
	}
	while (n > 0)
	{
		a[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (a);
}
