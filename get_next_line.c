/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:08:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2017/11/29 13:57:22 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_fd_buff(const int fd, t_list **fd_lst)
{
	char	*fd_buff;
	t_list	*prev;
	t_list	*tmp;

	prev = NULL;
	while (*fd_lst)
	{
		if ((*fd_lst)->content_size == (size_t)fd)
		{
			fd_buff = (*fd_lst)->content;
			if (prev)
				prev->next = (*fd_lst)->next;
			else
			{
				tmp = *fd_lst;
				*fd_lst = (*fd_lst)->next;
			}
			prev ? free(*fd_lst) : free(tmp);
			return (fd_buff);
		}
		prev = *fd_lst;
		fd_lst = &(*fd_lst)->next;
	}
	return (NULL);
}

static int	ft_save_fd_buff(const int fd, t_list **fd_lst, char *fd_buff)
{
	char	*start;
	t_list	*new_fd;

	if (ft_strlen(fd_buff) - ft_strlen_c(fd_buff, '\n') > 1)
	{
		if (!(new_fd = (t_list*)malloc(sizeof(t_list))))
			return (1);
		start = fd_buff + ft_strlen_c(fd_buff, '\n') + 1;
		new_fd->content_size = fd;
		new_fd->content = ft_strsub(start, 0, ft_strlen(start));
		new_fd->next = NULL;
		ft_lstadd_end(fd_lst, new_fd);
	}
	free(fd_buff);
	return (0);
}

static int	read_to_newline(const int fd, char **fd_buff)
{
	char			*read_b;
	char			*tmp;
	ssize_t			count;

	if (!(read_b = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	while ((count = read(fd, read_b, BUFF_SIZE)))
	{
		if (count == -1)
			return (1);
		tmp = *fd_buff;
		*fd_buff = *fd_buff ? ft_strjoin(*fd_buff, read_b)
			: ft_strjoin("", read_b);
		free(tmp);
		if (ft_strlen_c(read_b, '\n') != ft_strlen(read_b))
			break ;
		ft_bzero(read_b, BUFF_SIZE);
	}
	free(read_b);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	char			*fd_buff;
	static t_list	*fd_lst;

	if (!line || fd < 0)
		return (-1);
	*line = NULL;
	fd_buff = ft_get_fd_buff(fd, &fd_lst);
	if (!fd_buff
		|| (fd_buff && (ft_strlen_c(fd_buff, '\n') == ft_strlen(fd_buff))))
		if (read_to_newline(fd, &fd_buff))
			return (-1);
	if (!fd_buff)
		return (0);
	if (!(*line = ft_strsub(fd_buff, 0, ft_strlen_c(fd_buff, '\n'))))
		return (-1);
	if (ft_save_fd_buff(fd, &fd_lst, fd_buff))
		return (-1);
	return (1);
}
