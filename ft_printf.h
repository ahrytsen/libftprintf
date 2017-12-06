/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 21:04:05 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/06 14:04:19 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_PRINTF_H
# define	FT_PRINTF_H

extern char 	g_specs[];
extern char		g_flags[];

typedef struct	s_arg
{
	union
	{
		char	c;
		int		i;
		void	*p;
		long	l;
		double	d;
		float	f;
	};
	char	flags[6];
	int		width;
	int 	precision;
	char	length[3];
	char	specifier;
}				t_arg;

typedef 		void (*func)(t_ype);
int				ft_printf(const char * restrict format, ...);

#endif
