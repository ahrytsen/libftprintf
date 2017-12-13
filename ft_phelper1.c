/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:55:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/13 21:06:18 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_getstr(va_list *ap, t_arg *arg)
{
	if (arg->specifier == 's')
		return (ft_strdup(va_arg(*ap, char*)));
	return (0);
}

char	*ft_decimal(va_list *ap, t_arg *arg)
{
	char	*res;
	int		num;
	char	*tmp;

	num = va_arg(*ap, int);
	res = ft_itoa(num);
	tmp = res;
	if (num >= 0)
	{
		if (ft_strchr(arg->flags, '+'))
			res = ft_strjoin(tmp, "+");
		else if (ft_strchr(arg->flags, ' '))
			res = ft_strjoin(tmp, " ");
//		free(tmp);
	}
	return (res);
}

char	*ft_undef(t_arg *arg)
{
	char *lol;

	lol = NULL;
	arg->width = 1;
	return (lol);
	}
