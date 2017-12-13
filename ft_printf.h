/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 19:54:49 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/13 20:56:04 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct	s_color
{
	char	*color_name;
	char	*color_cod;
}				t_color;
typedef struct	s_conv
{
	char *conv;
	char *(*ft_phelper)();
}				t_conv;
typedef struct	s_arg
{
	char	flags[6];
	int		width;
	int		is_prec;
	int		prec;
	char	*len;
	char	specifier;
}				t_arg;

int				ft_printf(const char *format, ...);
char			*ft_getstr(va_list *ap, t_arg *arg);
char			*ft_decimal(va_list *ap, t_arg *arg);
char			*ft_undef(t_arg *arg);

#endif










