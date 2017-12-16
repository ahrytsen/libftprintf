/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pbuf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:18:01 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/12/16 20:22:56 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_buf(int c)
{
	char	buf[5];
	int		len;

	ft_bzero(buf, 5);
	if (c <= 0x7F && (len = 1))
		buf[0] = c;
	else if (c <= 0x7FF && (len = 2))
	{
		buf[0] = (c >> 6) + 0xC0;
		buf[1] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0xFFFF && (len = 3))
	{
		buf[0] = (c >> 12) + 0xE0;
		buf[1] = ((c >> 6) & 0x3F) + 0x80;
		buf[3] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0x10FFFF && (len = 4))
	{
		buf[0] = (c >> 18) + 0xF0;
		buf[1] = ((c >> 12) & 0x3F) + 0x80;
		buf[2] = ((c >> 6) & 0x3F) + 0x80;
		buf[3] = (c & 0x3F) + 0x80;
	}
	ft_putstr_buf(buf, len);
}

void	ft_putstr_buf(char *str, size_t len)
{
	while (len-- && g_buf)
		if (g_buf->len == PBS - 1)
		{
			g_buf->next = ft_newbuf();
			g_buf = g_buf->next;
		}
		else
			g_buf->str[g_buf->len++] = *str++;
}

void	ft_putustr_buf(int *str, size_t len)
{
	while (len-- && g_buf)
		ft_putchar_buf(*str++);
}

t_buf	*ft_newbuf(void)
{
	t_buf	*new_buf;

	if (!(new_buf = ft_memalloc(sizeof(t_buf))))
		return (NULL);
	if (!(new_buf->str = malloc(PBS)))
	{
		free(new_buf);
		return (NULL);
	}
	return (new_buf);
}
