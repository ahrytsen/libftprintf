/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfloat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:16:04 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/28 16:45:07 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline void	ft_pfd(t_buf *pbuf, va_list *ap, t_arg *arg)
{
	char	*tmp[3];
	int		len[2];

	tmp[2] = ft_dtoa(va_arg(*ap, double), arg->is_prec ? arg->prec : 6);
	tmp[0] = (*tmp[2] == '-') ? "-" : NULL;
	(ft_strchr(arg->flags, '+') && !tmp[0]) ? tmp[0] = "+" : 0;
	(ft_strchr(arg->flags, ' ') && !tmp[0]) ? tmp[0] = " " : 0;
	len[0] = ft_strlen(tmp[2]);
	if (*tmp[2] == '-')
		len[0]--;
	arg->is_prec = 0;
	ft_print_arg(pbuf, arg, tmp, len);
	free(tmp[2]);
}
