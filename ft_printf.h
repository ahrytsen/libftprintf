/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 19:54:49 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/09 20:43:06 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef char	*(*t_phelp)();

typedef enum
{
	s = 0, S, p, di, D, oO, u, U, xX, c, C, n, eE, fF, gG, aA, count_convs
}	t_convs;
typedef enum
{
	hh = 0, h, l, ll, j, z, L, count_lflags
}	t_lflags;
typedef struct	s_arg
{
	char	flags[6];
	int		width;
	int		is_precision;
	int		precision;
	char	length[3];
	char	specifier;
}				t_arg;

int				ft_printf(const char *restrict format, ...);

#endif







