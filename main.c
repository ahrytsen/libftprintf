/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:17:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/25 21:00:29 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <libc.h>
#include <locale.h>

int	main()
{
	setlocale(LC_ALL, "");
//	printf("\n%d\n", printf("%llX", 4294967296));
	printf("\n%d\n", ft_printf("%llX", 4294967296));
}
