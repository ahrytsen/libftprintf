/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:17:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/18 16:00:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <libc.h>
#include <locale.h>

int	main()
{
	setlocale(LC_ALL, "");
	int width = 0x00A2;
//	char *s = ft_strdup("some string");
	printf("\n%d\n", printf("%#x", (size_t)-5));
//	printf("\n%d\n", ft_printf("%5.5R"));
}
