/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:16:42 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/28 16:12:44 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static double	ft_round(int precision)
{
	double	round;

	round = 0.1;
	while (precision-- > 1)
		round *= 0.1;
	return (round * 0.5);
}

char			*ft_dtoa(double nbr, int precision)
{
	char	*snbr;
	char	*remainder;
	int		i;

	snbr = ft_ltoa((long)nbr);
	nbr *= nbr < 0 ? -1 : 1;
	nbr -= (long)nbr;
	i = 1;
	if (precision > 0)
	{
		remainder = (char*)malloc(sizeof(char) * (precision + 2));
		*remainder = '.';
		remainder[precision + 1] = 0;
		nbr += ft_round(precision);
		while (precision--)
		{
			remainder[i++] = (long)(nbr * 10) + '0';
			nbr = nbr * 10 - (long)(nbr * 10);
		}
		snbr = ft_strextend(snbr, remainder);
	}
	return (snbr);
}
