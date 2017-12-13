/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strextend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:18:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/13 21:10:17 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strextend(char *s1, char *s2)
{
	char *res;

	res = ft_strjoin(s1, s2);
//	free(s1);
//	free(s2);
	return (res);
}
