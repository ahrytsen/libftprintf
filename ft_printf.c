/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:08:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/06 22:13:52 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

char	g_specs[] = "sSpdDioOuUxXcC%";
char	g_flags[] = "#0-+ ";
char	*get_format(va_list ap, char *format, t_arg *arg)
{
	ft_bzero(arg, sizeof(t_arg));

}
int		ft_printf(const char * restrict format, ...)
{
	int		ret;
	t_arg	arg;
	va_list	ap;

	ret = 0;
	va_start(ap, format);
	while(*format)
	{
		ft_putchar(*format);
		if (*format == '%')
		{

		}
		else
		{
			ft_putchar(*format);
			symbols++;
		}
		format++;
	}
	return (symbols);
}
