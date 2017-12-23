/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:17:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/23 03:55:23 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <libc.h>
#include <locale.h>

int	main()
{
	printf("\n%d\n", printf("%d", 5));
	printf("\n%d\n", ft_printf("%4.3d", 65));
}
