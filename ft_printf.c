/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:08:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/30 11:09:07 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const static t_conv		g_phelper[] =
{
	{"sS", &ft_str},
	{"diD", &ft_int},
	{"uUpxXoOb", &ft_base},
	{"fFeE", &ft_pfloat},
/*
**	{"gG", },
**	{"aA", },
*/
	{NULL, NULL}
};
const static t_color	g_colors[] =
{
	{"{eoc}", "\033[0m"}, {"{default}", "\033[39m"},
	{"{black}", "\033[30m"}, {"{red}", "\033[31m"},
	{"{green}", "\033[32m"}, {"{yellow}", "\033[33m"},
	{"{blue}", "\033[34m"}, {"{magenta}", "\033[35m"},
	{"{cyan}", "\033[36m"}, {"{l_gray}", "\033[37m"},
	{"{d_gray}", "\033[90m"}, {"{l_red}", "\033[91m"},
	{"{l_green}", "\033[92m"}, {"{l_yellow}", "\033[93m"},
	{"{l_blue}", "\033[94m"}, {"{l_magenta}", "\033[95m"},
	{"{l_cyan}", "\033[96m"}, {"{white}", "\033[97m"},
	{"{b_default}", "\033[49m"}, {"{b_black}", "\033[40m"},
	{"{b_red}", "\033[41m"}, {"{b_green}", "\033[42m"},
	{"{b_yellow}", "\033[43m"}, {"{b_blue}", "\033[44m"},
	{"{b_magenta}", "\033[45m"}, {"{b_cyan}", "\033[46m"},
	{"{b_l_gray}", "\033[47m"}, {"{b_d_gray}", "\033[100m"},
	{"{b_l_red}", "\033[101m"}, {"{b_l_green}", "\033[102m"},
	{"{b_l_yellow}", "\033[103m"}, {"{b_l_blue}", "\033[104m"},
	{"{b_l_magenta}", "\033[105m"}, {"{b_l_cyan}", "\033[106m"},
	{"{b_white}", "\033[107m"}, {NULL, NULL}
};

static const char	*ft_get_format(va_list *ap, const char *format, t_arg *arg)
{
	int	i;

	i = 0;
	ft_bzero(arg, sizeof(t_arg));
	while (*format)
	{
		if (*format && ft_strchr("#0-+ '", *format))
		{
			if (!ft_strchr(arg->flags, *format) && i < 6)
				arg->flags[i++] = *format;
		}
		else if ((*format >= '0' && *format <= '9') || *format == '*')
			ft_get_width(&format, ap, arg);
		else if (*format == '.')
			ft_get_prec(&format, ap, arg);
		else if (!ft_get_len(&format, arg))
		{
			arg->spec = *format;
			break ;
		}
		format++;
	}
	return (*format ? ++format : format);
}

static void			ft_get_color(const char **format, t_buf **pbuf)
{
	int	i;

	i = 0;
	while (g_colors[i].color_name
		&& ft_strncmp(*format, g_colors[i].color_name,
						ft_strlen(g_colors[i].color_name)))
		i++;
	if (g_colors[i].color_name)
	{
		ft_putstr_buf(pbuf, g_colors[i].color_cod,
					ft_strlen(g_colors[i].color_cod));
		*format += ft_strlen_c(*format, '}') + 1;
	}
	else
	{
		ft_putchar_buf(pbuf, **format);
		*format += 1;
	}
}

int					ft_printf(const char *format, ...)
{
	t_arg		arg;
	va_list		ap;
	t_buf		pb;
	t_buf		*pbuf;
	int			i;

	ft_bzero(&pb, sizeof(t_buf));
	pbuf = format ? &pb : NULL;
	format ? va_start(ap, format) : 0;
	while (pbuf && *format)
		if (*format == '%' && !(i = 0))
		{
			format = ft_get_format(&ap, format + 1, &arg);
			while (g_phelper[i].conv && !ft_strchr(g_phelper[i].conv, arg.spec))
				i++;
			(!arg.spec || !g_phelper[i].conv) ? ft_undef(&pbuf, &ap, &arg)
				: g_phelper[i].ft_phelper(&pbuf, &ap, &arg);
		}
		else if (*format == '{')
			ft_get_color(&format, &pbuf);
		else
			ft_putchar_buf(&pbuf, *format++);
	format ? va_end(ap) : 0;
	return (ft_print_buf(pbuf, &pb));
}
