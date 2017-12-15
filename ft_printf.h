/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 19:54:49 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/15 20:54:00 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define MOD(a)(a >= 0 ? a : -a)
# define PBS  65535
typedef struct	s_buf
{
	size_t			len;
	char			*str;
	struct s_buf	*next;
}				t_buf;
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
	char	spec;
}				t_arg;

int				ft_printf(const char *format, ...);
void			ft_pbufext(t_buf *buf, char *str, size_t len);
char			*ft_getstr(va_list *ap, t_arg *arg);
char			*ft_int(va_list *ap, t_arg *arg);
char			*ft_undef(t_arg *arg);

#endif
