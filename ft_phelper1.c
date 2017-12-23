/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:55:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/23 05:06:34 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_filler(t_arg *arg, ssize_t width)
{
	char	filler;

	filler = (!(arg->is_prec && ft_strchr("diDuUpoObxX", arg->spec))
			  && !ft_strchr(arg->flags, '-') && arg->width >= 0
			  && ft_strchr(arg->flags, '0')) ? '0' : ' ';
	while (width-- > 0)
		ft_putchar_buf(filler);
}

static long	ft_getnbr(va_list *ap, t_arg *arg)
{
	long	nbr;

	nbr = ((arg->spec == 'p') || (arg->len && ft_strchr("lzj", arg->len[0])))
		? va_arg(*ap, long) : va_arg(*ap, int);
	if (arg->len && !ft_strcmp("hh", arg->len))
		nbr = ft_strchr("di", arg->spec) ? (char)nbr : (unsigned char)nbr;
	else if (arg->len && !ft_strcmp("h", arg->len))
		nbr = ft_strchr("di", arg->spec) ? (short)nbr : (unsigned short)nbr;
	else if (!arg->len && arg->spec != 'p')
		nbr = ft_strchr("di", arg->spec) ? (int)nbr : (unsigned int)nbr;
	return (nbr);
}

void		ft_str(va_list *ap, t_arg *arg)
{
	void	*s;
	ssize_t	len;

	if (!(s = va_arg(*ap, void*)))
		arg->spec = 's';
	!s ? s = "(null)" : 0;
	len = (arg->spec == 'S') || (arg->len && !ft_strcmp(arg->len, "l"))
		? ft_strulen(s) : ft_strlen(s);
	arg->is_prec && len > MOD(arg->prec) ? len = MOD(arg->prec) : 0;
	if (ft_strchr(arg->flags, '-') || arg->width < 0)
		(arg->spec == 'S' || (arg->len && !ft_strcmp(arg->len, "l")))
			? ft_putustr_buf(s, len) : ft_putstr_buf(s, len);
	len < MOD(arg->width) ? ft_filler(arg, MOD(arg->width) - len) : 0;
	if (!ft_strchr(arg->flags, '-') && arg->width >= 0)
		(arg->spec == 'S' || (arg->len && !ft_strcmp(arg->len, "l")))
			? ft_putustr_buf(s, len) : ft_putstr_buf(s, len);
}

void	ft_int(va_list *ap, t_arg *arg)
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
	tmp[1] = arg->is_prec && arg->prec > len[0]
		? ft_memalloc(arg->prec - len[0] + 1) : NULL;
	tmp[1] ? ft_memset(tmp[1], '0', arg->prec - len[0]) : 0;
	(tmp[0] = ft_strjoin(tmp[0], tmp[1])) ? free(tmp[1]) : 0;
	len[1] = MOD(arg->width) - len[0] - (tmp[0] ? ft_strlen(tmp[0]) : 0);
	(arg->width >= 0 && (arg->is_prec || !ft_strchr(arg->flags, '0'))
	 && !ft_strchr(arg->flags, '-') && len[1] > 0) ? ft_filler(arg, len[1]) : 0;
	tmp[0] ? ft_putstr_buf(tmp[0], ft_strlen(tmp[0])) : 0;
	free(tmp[0]);
	(!ft_strchr(arg->flags, '-') && arg->width >= 0 && len[1] > 0
	 && ft_strchr(arg->flags, '0') && !arg->is_prec) ? ft_filler(arg, len[1]) : 0;
	ft_putstr_buf(tmp[2] + (*tmp[2] == '-' ? 1 : 0), len[0]);
	free(tmp[2]);
	if ((ft_strchr(arg->flags, '-') || arg->width >= 0) && len[1] > 0)
		ft_filler(arg, len[1]);
}

void	ft_base(va_list *ap, t_arg *arg)
{
	char	*tmp[3];
	int		len[2];
	int		base;

	base = (arg->spec == 'X' || arg->spec == 'x' || arg->spec == 'p') ? 16 : 2;
	base = (arg->spec == 'O' || arg->spec == 'o') ? 8 : base;
	tmp[2] = ft_ultoa_base(ft_getnbr(ap, arg), base, arg->spec == 'X' ? 'A' : 'a');
	tmp[0] = (arg->spec == 'X' || arg->spec == 'p') ? "0X" : NULL;
	(arg->spec == 'x') ? tmp[0] = "0x" : 0;
	(arg->spec == 'o' || arg->spec == 'O') ? tmp[0 = ]"0" : 0;
	len[0] = ft_strlen(tmp[2]);
	tmp[1] = arg->is_prec && arg->prec > len[0]
		? ft_memalloc(arg->prec - len[0] + 1) : NULL;
	tmp[1] ? ft_memset(tmp[1], '0', arg->prec - len[0]) : 0;
	(tmp[0] = ft_strjoin(tmp[0], tmp[1])) ? free(tmp[1]) : 0;
	len[1] = MOD(arg->width) - len[0] - (tmp[0] ? ft_strlen(tmp[0]) : 0);
	(arg->width >= 0 && (arg->is_prec || !ft_strchr(arg->flags, '0'))
	 && !ft_strchr(arg->flags, '-') && len[1] > 0) ? ft_filler(arg, len[1]) : 0;
	tmp[0]  ? ft_putstr_buf(tmp[0], ft_strlen(tmp[0])) : 0;
	free(tmp[0]);
	(!ft_strchr(arg->flags, '-') && arg->width >= 0 && len[1] > 0
	 && ft_strchr(arg->flags, '0') && !arg->is_prec) ? ft_filler(arg, len[1]) : 0;
	ft_putstr_buf(tmp[2] + (*tmp[2] == '-' ? 1 : 0), len[0]);
	free(tmp[2]);
}

void	ft_undef(va_list *ap, t_arg *arg)
{
	int	c[2];
	int	charlen;

	c[1] = 0;
	c[0] = (arg->spec == 'C' || arg->spec == 'c') ? va_arg(*ap, int) : arg->spec;
	(arg->spec == 'c' && (!arg->len || (arg->len && ft_strcmp(arg->len, "l"))))
		? c[0] = (char)c[0] : 0;
	if (ft_strchr(arg->flags, '-') || arg->width < 0)
		ft_putchar_buf(c[0]);
	charlen = ft_strulen(c);
	ft_filler(arg, MOD(arg->width) - (charlen ? charlen : 1));
	if (!ft_strchr(arg->flags, '-') && arg->width >= 0)
		ft_putchar_buf(c[0]);
}
