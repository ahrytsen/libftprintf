/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:55:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/18 22:33:04 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_filler(t_arg *arg, ssize_t width)
{
	char	filler;

	filler = (!ft_strchr(arg->flags, '-') && arg->width >= 0
			  && ft_strchr(arg->flags, '0')) ? '0' : ' ';
	while (width-- > 0)
		ft_putchar_buf(filler);
}

static long	ft_getnbr(va_list *ap, t_arg *arg)
{
	long	nbr;

	nbr = ((ft_strchr("di", arg->spec) && !arg->len)
			|| (arg->len && arg->len[0] == 'h'))
		? va_arg(*ap, int) : va_arg(*ap, long);
	(arg->len && !ft_strcmp("hh", arg->len)) ? nbr = (char)nbr : 0;
	(arg->len && !ft_strcmp("h", arg->len)) ? nbr = (short)nbr : 0;
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
	arg->is_prec && len > arg->prec ? len = arg->prec : 0;
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
	long	nbr;
	char	*snbr;

	nbr = ft_getnbr(ap, arg);
	snbr = ft_ultoa_base(nbr, 10, 0, (ft_strchr("diD", arg->spec) ? 0 : 1));
	ft_putstr_buf(snbr, ft_strlen(snbr));
	free(snbr);
}

/*void	ft_base(va_list *ap, t_arg *arg)
{
	char	*res;
	long	num;
	int		len;
	char	pref[3];
	int		base;

	num = ft_strchr("di", arg->spec) ? va_arg(*ap, int) : va_arg(*ap, long);
	base = (arg->spec == 'X' || arg->spec == 'x') ? 16 : 10;
	base = (arg->spec == 'O' || arg->spec == 'o') ? 8 : base;
	res = ft_ultoa_base(num, base, 'A' + arg->spec - ft_toupper(arg->spec),
						ft_strchr("diD", arg->spec));
	pref =
	tmp = res;
	if (num >= 0 && MOD(arg->width) <= (int)ft_strlen(res) && base == 10)
	{
		if (ft_strchr(arg->flags, '+'))
			res = ft_strjoin("+", tmp);
		else if (ft_strchr(arg->flags, ' '))
			res = ft_strjoin(" ", tmp);
		free(tmp);
	}
	}*/

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
