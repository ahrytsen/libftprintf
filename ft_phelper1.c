/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:55:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/14 18:36:32 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_getstr(va_list *ap, t_arg *arg)
{
	if (arg->spec == 's')
		return (ft_strdup(va_arg(*ap, char*)));
	return (0);
}

char	*ft_decimal(va_list *ap, t_arg *arg)
{
	char	*res;
	long	num;
	char	*tmp;
	int		base;

	num = ft_strchr("di", arg->spec) ? va_arg(*ap, int) : va_arg(*ap, long);
	base = (arg->spec == 'X' || arg->spec == 'x') ? 16 : 10;
	base = (arg->spec == 'O' || arg->spec == 'o') ? 8 : base;
	res = ft_itoa_base(num, base, 'A' + arg->spec -ft_toupper(arg->spec));
	tmp = res;
	if (num >= 0 && MOD(arg->width) <= (int)ft_strlen(res) && base == 10)
	{
		if (ft_strchr(arg->flags, '+'))
			res = ft_strjoin("+", tmp);
		else if (ft_strchr(arg->flags, ' '))
			res = ft_strjoin(" ", tmp);
		free(tmp);
	}
	return (res);
}

char	*ft_undef(t_arg *arg)
{
	char *res;

	res = ft_memalloc(2);
	*res = arg->spec;
	return (res);
}
