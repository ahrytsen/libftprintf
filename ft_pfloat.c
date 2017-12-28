/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfloat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:16:04 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/28 20:47:55 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline void	ft_pfd(t_buf **pbuf, va_list *ap, t_arg *arg)
{
	char	*tmp[3];
	int		len[2];
	double	nbr;
	char	*f;

	nbr = va_arg(*ap, double);
	if (nbr != nbr)
		tmp[2] = arg->spec == 'f' ? ft_strdup("nan") : ft_strdup("NAN");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'f')
		tmp[2] = nbr < 0 ? ft_strdup("-inf") : ft_strdup("inf");
	else if (nbr == 1.0 / 0.0 && arg->spec == 'F')
		tmp[2] = nbr < 0 ? ft_strdup("-INF") : ft_strdup("INF");
	else
		tmp[2] = ft_dtoa(nbr, arg->is_prec ? arg->prec : 6);
	tmp[0] = (*tmp[2] == '-') ? "-" : NULL;
	(ft_strchr(arg->flags, '+') && !tmp[0]) ? tmp[0] = "+" : 0;
	(ft_strchr(arg->flags, ' ') && !tmp[0]) ? tmp[0] = " " : 0;
	len[0] = ft_strlen(tmp[2]);
	(*tmp[2] == '-') ? len[0]-- : 0;
	arg->is_prec = 0;
	if ((nbr != nbr || nbr == 1.0 / 0.0) && (f = ft_strchr(arg->flags, '0')))
		*f = 'r';
	ft_print_arg(pbuf, arg, tmp, len);
	free(tmp[2]);
}
