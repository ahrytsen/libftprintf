/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phendler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:55:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/26 21:06:54 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline void	ft_print_arg(t_buf *pbuf, t_arg *arg, char **tmp, int *len)
{
	tmp[1] = arg->is_prec && arg->prec > len[0]
		? ft_memalloc(arg->prec - len[0] + 1) : NULL;
	if (tmp[1])
		ft_memset(tmp[1], '0', arg->prec - len[0]
			- (tmp[0] && (ft_strchr("oO", arg->spec)) ? 1 : 0));
	(tmp[0] = ft_strjoin(tmp[0], tmp[1])) ? free(tmp[1]) : 0;
	len[1] = MOD(arg->width) - len[0] - (tmp[0] ? ft_strlen(tmp[0]) : 0);
	(len[1] > 0 && arg->width >= 0 && !ft_strchr(arg->flags, '-')
	&& (arg->is_prec || !ft_strchr(arg->flags, '0')))
		? ft_filler(pbuf, arg, len[1]) : 0;
	tmp[0] ? ft_putstr_buf(pbuf, tmp[0], ft_strlen(tmp[0])) : 0;
	free(tmp[0]);
	(!arg->is_prec && arg->width >= 0 && len[1] > 0
	&& ft_strchr(arg->flags, '0') && !ft_strchr(arg->flags, '-'))
		? ft_filler(pbuf, arg, len[1]) : 0;
	ft_putstr_buf(pbuf, tmp[2] + (*tmp[2] == '-' ? 1 : 0), len[0]);
	(len[1] > 0 && (ft_strchr(arg->flags, '-') || arg->width < 0))
		? ft_filler(pbuf, arg, len[1]) : 0;
}

void		ft_str(t_buf *pbuf, va_list *ap, t_arg *arg)
{
	void	*s;
	ssize_t	len;
	ssize_t	i[2];

	if (!(s = va_arg(*ap, void*)))
		arg->spec = 's';
	!s ? s = "(null)" : 0;
	len = (arg->spec == 'S') || (arg->len && !ft_strcmp(arg->len, "l"))
		? ft_strulen(s) : ft_strlen(s);
	if ((arg->spec == 'S' || (arg->len && !ft_strcmp(arg->len, "l")))
		&& arg->is_prec && len > arg->prec && !(len = 0))
	{
		ft_bzero(i, sizeof(ssize_t) * 2);
		while ((i[1] += ft_wcharlen(((int*)s)[i[0]++])) <= arg->prec)
			len = i[1];
	}
	else if (arg->is_prec && len > arg->prec)
		len = arg->prec;
	if (arg->width < 0 || ft_strchr(arg->flags, '-'))
		(arg->spec == 'S' || (arg->len && !ft_strcmp(arg->len, "l")))
			? ft_putustr_buf(pbuf, s, len) : ft_putstr_buf(pbuf, s, len);
	len < MOD(arg->width) ? ft_filler(pbuf, arg, MOD(arg->width) - len) : 0;
	if (arg->width >= 0 && !ft_strchr(arg->flags, '-'))
		(arg->spec == 'S' || (arg->len && !ft_strcmp(arg->len, "l")))
			? ft_putustr_buf(pbuf, s, len) : ft_putstr_buf(pbuf, s, len);
}

void		ft_int(t_buf *pbuf, va_list *ap, t_arg *arg)
{
	char	*tmp[3];
	int		len[2];

	tmp[2] = ft_ltoa(ft_getnbr(ap, arg));
	tmp[0] = (*tmp[2] == '-') ? "-" : NULL;
	(ft_strchr(arg->flags, '+') && !tmp[0]) ? tmp[0] = "+" : 0;
	(ft_strchr(arg->flags, ' ') && !tmp[0]) ? tmp[0] = " " : 0;
	len[0] = ft_strlen(tmp[2]);
	if (*tmp[2] == '-' || (arg->is_prec && !arg->prec && *tmp[2] == '0'))
		len[0]--;
	ft_print_arg(pbuf, arg, tmp, len);
	free(tmp[2]);
}

void		ft_base(t_buf *pbuf, va_list *ap, t_arg *arg)
{
	char	*tmp[3];
	int		len[2];
	int		base;

	base = (arg->spec == 'X' || arg->spec == 'x' || arg->spec == 'p') ? 16 : 10;
	(arg->spec == 'O' || arg->spec == 'o') ? base = 8 : 0;
	arg->spec == 'b' ? base = 2 : 0;
	tmp[2] = ft_ultoa_base(ft_getnbr(ap, arg),
						base, arg->spec == 'X' ? 'A' : 'a');
	tmp[0] = (arg->spec == 'x') ? "0x" : NULL;
	(arg->spec == 'X') ? tmp[0] = "0X" : 0;
	(arg->spec == 'o' || arg->spec == 'O') ? tmp[0] = "0" : 0;
	(*tmp[2] == '0' || !ft_strchr(arg->flags, '#')) ? tmp[0] = NULL : 0;
	(arg->spec == 'p') ? tmp[0] = "0x" : 0;
	len[0] = ft_strlen(tmp[2]);
	(arg->is_prec && !arg->prec && *tmp[2] == '0'
	&& !(ft_strchr("oO", arg->spec) && ft_strchr(arg->flags, '#')))
		? len[0]-- : 0;
	ft_print_arg(pbuf, arg, tmp, len);
	free(tmp[2]);
}

void		ft_undef(t_buf *pbuf, va_list *ap, t_arg *arg)
{
	int	c[2];
	int	*n;
	int	charlen;

	if (!arg->spec)
		return ;
	else if (arg->spec == 'n')
	{
		n = va_arg(*ap, void*);
		*n = pbuf->id * PBS + pbuf->len;
		return ;
	}
	c[1] = 0;
	c[0] = (arg->spec == 'C' || arg->spec == 'c')
		? va_arg(*ap, int) : arg->spec;
	(arg->spec == 'c' && (!arg->len || (arg->len && ft_strcmp(arg->len, "l"))))
		? c[0] = (char)c[0] : 0;
	if (ft_strchr(arg->flags, '-') || arg->width < 0)
		ft_putchar_buf(pbuf, c[0]);
	charlen = c[0] ? ft_strulen(c) : 1;
	ft_filler(pbuf, arg, MOD(arg->width) - charlen);
	if (!ft_strchr(arg->flags, '-') && arg->width >= 0)
		ft_putchar_buf(pbuf, c[0]);
}
