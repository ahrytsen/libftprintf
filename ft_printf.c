/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:08:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/26 02:57:58 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const static char		*g_len[] = {"hh", "ll", "h", "l", "j", "z", "L", NULL};
const static t_conv		g_phelper[] =
{
	{"sS", &ft_str},
	{"diD", &ft_int},
	{"uUpxXoOb", &ft_base},
/*	{"eE", },
	{"fF", },
	{"gG", },
	{"aA", },*/
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

/*static const char	*ft_get_format(va_list *ap, const char *format, t_arg *arg)
{
	int	i;

	i = 0;
	ft_bzero(arg, sizeof(t_arg));
	while (*format && ft_strchr("#0-+ ", *format) && i < 6)
		if (!ft_strchr(arg->flags, *format))
			arg->flags[i++] = *format++;
		else
			format++;
	(*format >= '0' && *format <= '9') ? arg->width = ft_atol(format) : 0;
	while (*format >= '0' && *format <= '9')
		format++;
	*format == '*' ? arg->width = va_arg(*ap, int) : 0;
	*format == '*' ? format++ : 0;
	if (*format == '.' && ++arg->is_prec)
		arg->prec = (*++format == '*') ? va_arg(*ap, int) : ft_atol(format);
	arg->prec < 0 ? arg->is_prec = 0 : 0;
	while ((*format >= '0' && *format <= '9') || *format == '*')
		format++;
	i = 0;
	while (g_len[i] && ft_strncmp(g_len[i], format, ft_strlen(g_len[i])))
		i++;
	arg->len = g_len[i];
	format += g_len[i] ? ft_strlen(g_len[i]) : 0;
	arg->spec = *format;
	return (*format ? ++format : format);
}*/

inline static int	ft_get_len(const char **format, t_arg *arg)
{
	int i;

	i = 0;
	while (g_len[i] && ft_strncmp(g_len[i], *format, ft_strlen(g_len[i])))
		i++;
	(g_len[i] && !arg->len) ? arg->len = g_len[i] : 0;
	*format += g_len[i] ? ft_strlen(g_len[i]) - 1 : 0;
	return (g_len[i] ? 1 : 0);
}

inline static void	ft_get_width(const char **format, va_list *ap, t_arg *arg)
{
	if (**format == '*')
		arg->width = va_arg(*ap, int);
	else if (**format >= '0' && **format <= '9')
	{
		arg->width = ft_atol(*format);
		while (*(*format + 1) >= '0' && *(*format + 1) <= '9')
			(*format)++;
	}
}

inline static void	ft_get_prec(const char **format, va_list *ap, t_arg *arg)
{
	if (*(*format + 1) == '*')
	{
		(*format)++;
		arg->prec = va_arg(*ap, int);
	}
	else
	{
		arg->prec = ft_atol(*format + 1);
		while (*(*format + 1) >= '0' && *(*format + 1) <= '9')
			(*format)++;
	}
	arg->prec > 0 ? arg->is_prec = 1 : 0;
}

static const char	*ft_get_format(va_list *ap, const char *format, t_arg *arg)
{
	int	i;

	i = 0;
	ft_bzero(arg, sizeof(t_arg));
	while (*format)
	{
		if (*format && ft_strchr("#0-+ ", *format))
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
			break;
		}
		format++;
	}
	return (*format ? ++format : format);
}

static void			ft_get_color(const char **format, t_buf *pbuf)
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

void print_arg(t_arg *arg)
{
	ft_putstr("Spec: ");
	ft_putchar(arg->spec);
	write(1, "\n", 1);
	ft_putstr("flags: ");
	ft_putendl(arg->flags);
	ft_putstr("Len: ");
	ft_putendl(arg->len);
	ft_putstr("Width: ");
	ft_putnbr(arg->width);
	write(1, "\n", 1);
	ft_putstr("Is prec: ");
	ft_putnbr(arg->is_prec);
	write(1, "\n", 1);
	ft_putstr("Prec: ");
	ft_putnbr(arg->prec);
	write(1, "\n", 1);
}

int					ft_printf(const char *format, ...)
{
	t_arg		arg;
	va_list		ap;
	t_buf		*pbuf[2];
	int			i;

	pbuf[0] = format ? ft_newbuf() : NULL;
	format ? va_start(ap, format) : 0;
	pbuf[1] = pbuf[0];
	while (pbuf[1] && *format)
		if (*format == '%' && !(i = 0))
		{
			format = ft_get_format(&ap, format + 1, &arg);
			//print_arg(&arg);
			while (g_phelper[i].conv && !ft_strchr(g_phelper[i].conv, arg.spec))
				i++;
			(!arg.spec || !g_phelper[i].conv) ? ft_undef(pbuf[1], &ap, &arg)
				: g_phelper[i].ft_phelper(pbuf[1], &ap, &arg);
		}
		else if (*format == '{')
			ft_get_color(&format, pbuf[1]);
		else
			ft_putchar_buf(pbuf[1], *format++);
	format ? va_end(ap) : 0;
	return (ft_print_buf(pbuf[1], pbuf[0]));
}
