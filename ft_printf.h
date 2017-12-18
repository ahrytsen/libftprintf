/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 19:54:49 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/18 15:20:57 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <locale.h>
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
	char	*conv;
	void	(*ft_phelper)();
}				t_conv;
typedef struct	s_arg
{
	char	flags[6];
	ssize_t	width;
	int		is_prec;
	ssize_t	prec;
	char	*len;
	char	spec;
}				t_arg;

extern t_buf	*g_buf;
extern char		g_flags[];
extern char		*g_len[];

t_buf			*ft_newbuf(void);
void			ft_putchar_buf(int c);
void			ft_putustr_buf(int *str, size_t len);
void			ft_putstr_buf(char *str, size_t len);
ssize_t			ft_print_buf(t_buf *buf);
int				ft_printf(const char *format, ...);
void			ft_str(va_list *ap, t_arg *arg);
void			ft_int(va_list *ap, t_arg *arg);
void			ft_undef(t_arg *arg);

#endif
