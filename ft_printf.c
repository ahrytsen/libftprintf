/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:08:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/18 16:15:35 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_buf		*g_buf;
char		g_flags[] = "#0-+ ";
char		*g_len[] = {"hh", "ll", "h", "l", "j", "z", "L", NULL};
t_conv		g_phelper[] =
{
	{"sS", &ft_str},
	{"diXxOo", &ft_int},
	/*{"pxX", &ft_hex},
	{"D", &ft_double},
	{"oO", &ft_octal},
	{"uU", &ft_unsig},
	{"cC", &ft_symbol},
	{"n", },
	{"eE", },
	{"fF", },
	{"gG", },
	{"aA", },*/
	{NULL, NULL}
};
t_color		g_colors[] =
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
	while (ft_strchr(g_flags, *format) && i < 6)
		if (!ft_strchr(arg->flags, *format))
			arg->flags[i++] = *format++;
		else
			format++;
	if ((*format >= '0' && *format <= '9') || *format == '*')
		arg->width = (*format == '*') ? va_arg(*ap, int) : ft_atol(format);
	while ((*format >= '0' && *format <= '9') || *format == '*')
		format++;
	if (*format == '.' && ++arg->is_prec)
		arg->prec = (*++format == '*') ? va_arg(*ap, int) : ft_atol(format);
	while ((*format >= '0' && *format <= '9') || *format == '*')
		format++;
	i = 0;
	while (g_len[i] && ft_strncmp(g_len[i], format, ft_strlen(g_len[i])))
		i++;
	arg->len = g_len[i];
	format += arg->len ? ft_strlen(arg->len) : 0;
	arg->spec = *format;
	return (*format ? ++format : format);
}

static void			ft_get_color(const char **format)
{
	int	i;

	i = 0;
	while (g_colors[i].color_name
		&& ft_strncmp(*format, g_colors[i].color_name,
						ft_strlen(g_colors[i].color_name)))
		i++;
	if (g_colors[i].color_name)
	{
		ft_putstr_buf(g_colors[i].color_cod, ft_strlen(g_colors[i].color_cod));
		*format += ft_strlen_c(*format, '}');
	}
	else
		ft_putchar_buf(*(*format++));
}

/*static char	*ft_prefix(char **res, t_arg *arg)
{
	char *pref;

	pref = NULL;
	if (ft_strchr("di", arg->spec))
	{
		if (ft_strchr(arg->flags, '+') && **res != '-')
			pref = ft_strdup("+");
		else if (ft_strchr(arg->flags, ' ') && **res != '-')
			pref = ft_strdup(" ");
		else if (**res == '-')
		{
			pref = *res;
			*res = ft_strsub(*res, 1, ft_strlen(*res + 1));
			free(pref);
			pref = ft_strdup("-");
		}

	}
	else if (ft_strchr("xX", arg->spec) && ft_strchr(arg->flags, '#'))
		pref = arg->spec == 'X' ? ft_strdup("0X") : ft_strdup("0x");
	else if (ft_strchr("oOb", arg->spec) && ft_strchr(arg->flags, '#'))
		pref = arg->spec == 'b' ? ft_strdup("b") : ft_strdup("0");
	return (pref);
	}*/

int				ft_printf(const char *format, ...)
{
	t_arg	arg;
	va_list	ap;
	t_buf	*buf_head;
	int		i;

	i = 0;
	g_buf = format ? ft_newbuf() : NULL;
	format ? va_start(ap, format) : 0;
	buf_head = g_buf;
	while (g_buf && *format)
		if (*format == '%')
		{
			format = ft_get_format(&ap, format + 1, &arg);
			while ( g_phelper[i].conv && !ft_strchr(g_phelper[i].conv, arg.spec))
				i++;
			g_phelper[i].conv ? g_phelper[i].ft_phelper(&ap, &arg) : ft_undef(&arg);
		}
		else if (*format == '{')
			ft_get_color(&format);
		else
			ft_putchar_buf(*format++);
	format ? va_end(ap) : 0;
	return (ft_print_buf(buf_head));
}
