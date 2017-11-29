/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:47:51 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/04 14:39:46 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	j;
	char	*new_string;

	j = 0;
	if (!s1 || !s2 || !(new_string = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	while (*s1)
		new_string[j++] = *s1++;
	while (*s2)
		new_string[j++] = *s2++;
	new_string[j] = 0;
	return (new_string);
}
