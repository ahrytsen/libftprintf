/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:17:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/15 13:23:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <libc.h>
#include <locale.h>

int	main()
{
	setlocale(LC_ALL, "");
	int width = 50;
	char *s = "some string";
	printf("\n%d\n", printf("lol kek %+#0*s", width, s));
//	printf("\n%d\n", ft_printf("lol kek %#0*h", width, 154442));
}
