/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:55:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/22 20:45:46 by ahrytsen         ###   ########.fr       */
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
	char	*sign;
	char	*snbr;
	char	*prec;
	int		len;

	snbr = ft_ltoa(ft_getnbr(ap, arg));
	sign = (*snbr == '-') ? "-" : "";
	(ft_strchr(arg->flags, '+') && !*sign) ? sign = "+" : 0;
	(ft_strchr(arg->flags, ' ') && !*sign) ? sign = " " : 0;
	len = ft_strlen(snbr);
	(*snbr == '-' || (arg->is_prec && !arg->prec && *snbr == '0')) ? len-- : 0;
	prec = arg->is_prec && arg->prec > len
		? ft_memalloc(arg->prec - len + 1) : NULL;
	prec ? ft_memset(prec, '0', arg->prec - len) : 0;
	(sign = ft_strjoin(sign, prec)) ? free(prec) : 0;
	if (ft_strchr(arg->flags, '-') || arg->width < 0
		|| (!ft_strchr(arg->flags, '-') && arg->width >= 0
			&& ft_strchr(arg->flags, '0') && !arg->is_prec))
		ft_putstr_buf(sign, ft_strlen(sign));
	if ((len += ft_strlen(sign)) < MOD(arg->width))
		ft_filler(arg, MOD(arg->width) - len);
	if ((!ft_strchr(arg->flags, '-') && arg->width >= 0)
			|| !ft_strchr(arg->flags, '0') && !arg->is_prec))
		ft_putstr_buf(sign, ft_strlen(sign));
	ft_putstr_buf(snbr + (*snbr == '-' ? 1 : 0), len);
	if (!ft_strchr(arg->flags, '-') && arg->width >= 0)
		(arg->spec == 'S' || (arg->len && !ft_strcmp(arg->len, "l")))
			? ft_putustr_buf(s, len) : ft_putstr_buf(s, len);
	free(snbr);
}

void	ft_base(va_list *ap, t_arg *arg)
{
	char	*res;
	size_t	num;
//	int		len;
	char	*pref;
	int		base;

	num = ft_getnbr(ap, arg);
	base = (arg->spec == 'X' || arg->spec == 'x' || arg->spec == 'p') ? 16 : 2;
	base = (arg->spec == 'O' || arg->spec == 'o') ? 8 : base;
	res = ft_ultoa_base(num, base, 'A' + arg->spec - ft_toupper(arg->spec));
	pref = (arg->spec == 'X' || arg->spec == 'p') ? "0X" : "b";
	pref = (arg->spec == 'x') ? "0x" : pref;
	pref = (arg->spec == 'o' || arg->spec == 'O') ? "0" : pref;
	if ((num || ft_strchr("oO", arg->spec)) && ft_strchr(arg->flags, '#'))
		ft_putstr_buf(pref, ft_strlen(pref));
	(!num  && arg->is_prec && !arg->prec) ? 0 : ft_putstr_buf(res, ft_strlen(res));
	free(res);
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
