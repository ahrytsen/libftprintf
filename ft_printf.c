/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:08:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/07 16:18:47 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

char	g_specs[] = "sSpdDioOuUxXcC%";
char	g_flags[] = "#0-+ ";

int		ft_error(char *s)
{
	free(*s);
	return (-1);
}

size_t	utf8len(char *s)
{
	size_t len = 0;
	while (*s)
		if ((*s++ & 0xC0) != 0x80)
			len++;
	return (len);
}

char	*ft_get_format(va_list ap, char *format, t_arg *arg)
{
	ft_bzero(arg, sizeof(t_arg));
	while (ft_strchr(g_flags, *format))
		if()
}
int		ft_printf(const char * restrict format, ...)
{
	char	*res;
	char	*tmp;
	t_arg	arg;
	va_list	ap;

	res = NULL;
	va_start(ap, format);
	while(*format)
	{
		if (*format == '%')
		{
			if (!(format = ft_get_format(ap, format + 1, &arg)))
				return (ft_error(res));
			tmp = res;
			ft_strjoin()
		}
		tmp = res;
		res = ft_strsub(format, 0, ft_strlen_c(format, '%'))
		format++;
	}
	write(1, res, ft_strlen(res));
	return (utf8len(res) + 1);
}
