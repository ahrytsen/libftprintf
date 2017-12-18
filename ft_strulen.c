/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strulen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 15:41:10 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/18 18:36:52 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strulen(int *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s <= 0x7F)
			len++;
		else if (*s <= 0x7FF)
			len += 2;
		else if (*s <= 0xFFFF)
			len += 3;
		else if (*s <= 0x1FFFFF)
			len += 4;
		else if (*s <= 0x3FFFFFF)
			len += 5;
		else
			len += 6;
		s++;
	}
	return (len);
}
