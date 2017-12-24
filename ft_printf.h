/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 19:54:49 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/24 15:54:28 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <locale.h>
# include "libft.h"

# define MOD(a)(a >= 0 ? a : -a)
# define PBS  10240

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
	char	*conv;
	void	(*ft_phelper)();
}				t_conv;
typedef struct	s_arg
{
	char		flags[6];
	ssize_t		width;
	int			is_prec;
	ssize_t		prec;
	const char	*len;
	char		spec;
}				t_arg;

t_buf			*ft_newbuf(void);
void			ft_putchar_buf(t_buf *pbuf, int c);
void			ft_putustr_buf(t_buf *pbuf, int *str, size_t len);
void			ft_putstr_buf(t_buf *pbuf, char *str, size_t len);
ssize_t			ft_print_buf(t_buf *pbuf, t_buf *pbuf_head);
int				ft_printf(const char *format, ...);
void			ft_str(t_buf *pbuf, va_list *ap, t_arg *arg);
void			ft_int(t_buf *pbuf, va_list *ap, t_arg *arg);
void			ft_base(t_buf *pbuf, va_list *ap, t_arg *arg);
void			ft_undef(t_buf *pbuf, va_list *ap, t_arg *arg);

#endif
