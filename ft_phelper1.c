/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 14:55:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/16 22:18:27 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_str(va_list *ap, t_arg *arg)
{
	void	*s;
	ssize_t	len;
	char	*filler;

	if (!(s = va_arg(*ap, void*)))
		arg->spec = 's';
	!s ? s = "(null)" : 0;
	len = (arg->spec == 'S') || (arg->len && !ft_strcmp(arg->len, "l"))
		? ft_strulen(s) : ft_strlen(s);
	arg->is_prec && len > arg->prec ? len = arg->prec : 0;
	filler = len < MOD(arg->width)
		? ft_memalloc(MOD(arg->width) - len + 1) : NULL;
	if (filler)
		(!ft_strchr(arg->flags, '-') && arg->width >= 0
		&& ft_strchr(arg->flags, '0') && !arg->is_prec)
			? ft_memset(filler, '0', MOD(arg->width) - len)
			: ft_memset(filler, ' ', MOD(arg->width) - len);
	if (ft_strchr(arg->flags, '-') || arg->width < 0)
		(arg->spec == 'S' || (arg->len && !ft_strcmp(arg->len, "l")))
			? ft_putustr_buf(s, len) : ft_putstr_buf(s, len);
	filler ? ft_putstr_buf(filler, ft_strlen(filler)) : 0;
	if (!ft_strchr(arg->flags, '-') && arg->width >= 0)
		(arg->spec == 'S' || (arg->len && !ft_strcmp(arg->len, "l")))
			? ft_putustr_buf(s, len) : ft_putstr_buf(s, len);
	free(filler);
}

void	ft_int(va_list *ap, t_arg *arg)
{
	char	*res;
	long	num;
	char	*tmp;
	int		base;

	num = ft_strchr("di", arg->spec) ? va_arg(*ap, int) : va_arg(*ap, long);
	base = (arg->spec == 'X' || arg->spec == 'x') ? 16 : 10;
	base = (arg->spec == 'O' || arg->spec == 'o') ? 8 : base;
	res = ft_itoa_base(num, base, 'A' + arg->spec - ft_toupper(arg->spec));
	tmp = res;
	if (num >= 0 && MOD(arg->width) <= (int)ft_strlen(res) && base == 10)
	{
		if (ft_strchr(arg->flags, '+'))
			res = ft_strjoin("+", tmp);
		else if (ft_strchr(arg->flags, ' '))
			res = ft_strjoin(" ", tmp);
		free(tmp);
	}
}

void	ft_undef(t_arg *arg)
{
	char	filler;
	ssize_t	width;

	width = MOD(arg->width);
	filler = (!ft_strchr(arg->flags, '-') && arg->width >= 0
			  && ft_strchr(arg->flags, '0')) ? '0' : ' ';
	if (ft_strchr(arg->flags, '-') || arg->width < 0)
		ft_putchar_buf(arg->spec);
	while (--width > 0)
		ft_putchar_buf(filler);
	if (!ft_strchr(arg->flags, '-') && arg->width >= 0)
		ft_putchar_buf(arg->spec);
}
