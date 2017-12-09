/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:08:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/09 20:42:49 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		g_specs[] = "sSpdDioOuUxXcC%";
char		g_flags[] = "#0-+ ";
char		g_length[] = "hljzL";
t_phelpe	g_phelpers[] =
{

};

size_t		ft_utf8len(char *s)
{
	size_t len;

	len = 0;
	while (*s)
		if ((*s++ & 0xC0) != 0x80)
			len++;
	return (len);
}

const char	*ft_get_format(va_list ap, const char *format, t_arg *arg)
{
	int	i;

	i = 0;
	ft_bzero(arg, sizeof(t_arg));
	while (ft_strchr(g_flags, *format) && i < 6)
		arg->flags[i++] = *format++;
	if ((*format >= '0' && *format <= '9') || *format == '*')
	{
		arg->width = (*format == '*') ? va_arg(ap, int) : ft_atoi(format);
		while (*format >= '0' && *format <= '9')
			format++;
	}
	if (*format == '.')
	{
		arg->is_precision = 1;
		arg->precision = (*++format == '*') ? va_arg(ap, int) : ft_atoi(format);
		while (*format >= '0' && *format <= '9')
			format++;
	}
	i = 0;
	while (ft_strchr(g_length, *format) && i < 2)
		arg->length[i++] = *format++;
	arg->specifier = *format;
	return (*format ? format + 1 : format);
}

char		*ft_arg_to_str(va_list ap, t_arg *arg)
{
	char *res;

	res = NULL;
	if (arg->specifier == 'd')
	{
		arg->i = va_arg(ap, int);
		res = ft_itoa(arg->i);
	}
	return (res);
}

int			ft_printf(const char *restrict format, ...)
{
	char	*res;
	t_arg	arg;
	va_list	ap;
	int		ret;

	res = format ? ft_memalloc(1) : NULL;
	format ? va_start(ap, format) : 0;
	while (res && *format)
		if (*format == '%' && (format = ft_get_format(ap, format + 1, &arg)))
			res = ft_strextend(res, ft_arg_to_str(ap, &arg));
		else if (*format == '{')
			format = ft_get_color(ap, format, &res);
		else
		{
			format += ft_strlen_c(format, '%');
			res = ft_strextend(res, ft_strsub(format, 0,
								ft_strlen_c(format, '%')));
		}
	format ? va_end(ap) : 0;
	ret = res ? write(1, res, ft_strlen(res)) : -1;
	free(res);
	return (ret);
}
