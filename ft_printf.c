/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:08:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/15 22:47:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_buf		g_buf;
char		g_flags[] = "#0-+ ";
char		*g_len[] = {"hh", "ll", "h", "l", "j", "z", "L", NULL};
t_conv		g_phelper[] =
{
	{"sS", &ft_getstr},
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

static const char	*ft_get_format(va_list *ap, const char **format, t_arg *arg)
{
	int	i;

	i = 0;
	ft_bzero(arg, sizeof(t_arg));
	while (ft_strchr(g_flags, **format) && i < 6)
		if (!ft_strchr(arg->flags, **format))
			arg->flags[i++] = *(*format)++;
		else
			(*format)++;
	if ((**format >= '0' && **format <= '9') || **format == '*')
		arg->width = (**format == '*') ? va_arg(*ap, int) : ft_atoi(*format);
	while ((**format >= '0' && **format <= '9') || **format == '*')
		format++;
	if (**format == '.' && ++arg->is_prec)
		arg->prec = (*++(*format) == '*') ? va_arg(*ap, int) : ft_atoi(format);
	while ((**format >= '0' && **format <= '9') || **format == '*')
		(*format)++;
	i = 0;
	while (g_len[i] && !ft_strncmp(g_len[i], *format, ft_strlen(g_len[i])))
		i++;
	arg->len = g_len[i];
	*format += arg->len ? ft_strlen(arg->len) : 0;
	arg->spec = *format;
	**format ? (*format)++ : 0;
}

static void			ft_get_color(const char **format)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_colors[i].color_name
		&& ft_strncmp(*format, g_colors[i].color_name,
						ft_strlen(g_colors[i].color_name)))
		i++;
	if (g_colors[i].color_name)
	{
		while (g_colors[i].color_cod[j] && g_buf)
			if (g_buf->len == PBS - 1)
				g_buf = (g_buf->next = ft_newbuf()) ? g_buf->next : NULL;
			else
				g_buf->str[g_buf->len++] = g_colors[i].color_cod[j++];
		*format += ft_strlen_c(*format, '}');
	}
	else
		g_buf->str[g_buf->len++] = **format++;
}

static char			*ft_prefix(char **res, t_arg *arg)
{
	char *pref;

	pref = NULL;
	if (ft_strchr("di", arg->spec) && **res != '-')
	{
		if (ft_strchr(arg->flags, '+') && **res != '-')
			pref = ft_strextend(ft_strdup("+"), *res);
		else if (ft_strchr(arg->flags, ' ') && **res != '-')
			pref = ft_strextend(ft_strdup(" "), *res);
		else if (**res == '-')
		{
			pref = *res;
			*res = ft_strsub(*res, 1, ft_strlen(*res + 1));
			free(pref);
			pref = ft_strdup("-");
		}
		return (pref);
	}
	if (ft_strchr("xX", arg->spec) && ft_strchr(arg->flags, '#'))
		pref = arg->spec == 'X' ? ft_strdup("0X") : ft_strdup("0x");
	if (ft_strchr("oOb", arg->spec) && ft_strchr(arg->flags, '#'))
		pref = arg->spec == 'b' ? ft_strdup("b") : ft_strdup("0");
	return (pref);
}

static void			ft_arg_to_str(va_list *ap, t_arg *arg)
{
	t_buf	*res;
	t_buf	tmp;
	char	*pref;
	int		i;

	i = 0;
	while ( g_phelper[i].conv && !ft_strchr(g_phelper[i].conv, arg->spec))
		i++;
	res = g_phelper[i].conv ? g_phelper[i].ft_phelper(ap, arg) : ft_undef(arg);
	arg->is_prec && ft_strchr("sS", arg->spec) ? res.str[arg->prec] = 0 : 0;
	pref = ft_prefix(&res, arg);
	tmp.str = ((i = res->len + (pref ? ft_strlen(pref) : 0)) < MOD(arg->width))
		? (char*)malloc(sizeof(char) * (MOD(arg->width) - i) + 1) : NULL;
	if (tmp.str)
		(!ft_strchr(arg->flags, '-') && arg->width >= 0
		 && ft_strchr(arg->flags, '0') && !arg->is_prec)
			? ft_memset(tmp.str, '0', MOD(arg->width) - i)
			: ft_memset(tmp.str, ' ', MOD(arg->width) - i);
	tmp.len = tmp.str ? ft_strlen(tmp.str) : 0;
	if (tmp && *tmp == '0')
		ft_pbufext(&tmp, res->str)
		ft_pbufext(&res, ft_strextend(&tmp, res->str)));
	res = ft_strextend(pref, res);
	return ((ft_strchr(arg->flags, '-') || arg->width < 0)
			? ft_strextend(res, tmp) : ft_strextend(tmp, res));
}

t_buf				*ft_newbuf()
{
	t_buf	*new_buf;

	if (!(new_buf = ft_memalloc(sizeof(t_buf))))
		return (NULL);
	if (!(new_buf.str = malloc(PBS)))
	{
		free(new_buf);
		return (NULL);
	}
	return (new_buf);
}

int					ft_printf(const char *format, ...)
{
	t_arg	arg;
	va_list	ap;
	t_buf	*buf_head;

	g_buf = format ? ft_newbuf() : NULL;
	format ? va_start(ap, format) : 0;
	buf_head = g_buf;
	while (g_buf && *format)
		if (g_buf>len == PBS - 1)
			g_buf = (g_buf->next = ft_newbuf()) ? g_buf->next : NULL;
		else if (*format == '%')
		{
			ft_get_format(&ap, &(++format), &arg);
			ft_arg_to_buff(&ap, &arg);
		}
		else if (*format == '{')
			ft_get_color(&format);
		else
			g_buf->str[g_buf->len++] = *format++;
	format ? va_end(ap) : 0;
	return (ft_print(buf_head));
}
