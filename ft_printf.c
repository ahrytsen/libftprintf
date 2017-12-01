/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:08:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/30 13:19:49 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int		printf(const char * restrict format, ...)
{
	int		symbols;
	va_list	arg;

	symbols = 0;
	va_start(arg, format);

}
