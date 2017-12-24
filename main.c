/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:17:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/24 18:24:01 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <libc.h>
#include <locale.h>

int	main()
{
	printf("\n%d\n", printf("%hU", 4294967296));
	printf("\n%d\n", ft_printf("%hU", 4294967296));
}
