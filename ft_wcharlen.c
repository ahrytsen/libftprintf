/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 16:55:19 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/25 16:57:59 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wcharlen(int c)
{
	int	len;

	len = 0;
	if (c <= 0x7F)
		len++;
	else if (c <= 0x7FF)
		len += 2;
	else if (c <= 0xFFFF)
		len += 3;
	else if (c <= 0x1FFFFF)
		len += 4;
	else if (c <= 0x3FFFFFF)
		len += 5;
	else
		len += 6;
	return (len);
}
