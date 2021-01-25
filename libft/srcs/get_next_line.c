/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:39:30 by aabelque          #+#    #+#             */
/*   Updated: 2018/06/20 18:14:45 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void			ft_free(t_list *elem)
{
	free((*elem).content);
	elem->content = NULL;
	elem->content_size = 0;
}

static	t_list			*ft_find(int fd, t_list **stock)
{
	t_list				*tmp;

	tmp = *stock;
	while (tmp && tmp->fd != fd)
		tmp = tmp->next;
	return (tmp);
}

static	char			*ft_get(int fd, t_list **stock)
{
	t_list				*elem;
	char				*debut;
	char				*fin;
	char				*tmp;

	elem = ft_find(fd, stock);
	if (elem->content == NULL)
		return (NULL);
	if ((fin = ft_strstr((char *)elem->content, "\n")) != NULL)
	{
		if (!(debut = ft_strsub((char *)elem->content, 0,
						(elem->content_size - ft_strlen(++fin) - 2))))
			return (NULL);
		tmp = elem->content;
		elem->content = (ft_strlen(fin) == 0) ? NULL : (void *)ft_strdup(fin);
		elem->content_size = ft_strlen(fin) + 1;
		free(tmp);
	}
	else
	{
		if (!(debut = ft_strdup((char *)elem->content)))
			return (NULL);
		ft_free(elem);
	}
	return (debut);
}

static	int				ft_check(int fd, char *buf, t_list **stock)
{
	t_list				*elem;
	char				*tmp;

	elem = ft_find(fd, stock);
	if (elem == NULL)
	{
		if (!(elem = (t_list *)ft_lstnew((void const *)buf,
						(ft_strlen(buf) + 1))))
			return (-1);
		elem->fd = fd;
		ft_pushback_list((t_list **)stock, (t_list *)elem);
	}
	else
	{
		if (!(tmp = ft_strjoin2((char *)elem->content, buf)))
			return (-1);
		free(elem->content);
		elem->content = (void *)tmp;
		elem->content_size = ft_strlen(tmp) + 1;
	}
	if (ft_strstr((char *)elem->content, "\n") != NULL)
		return (1);
	return (0);
}

int						get_next_line(int const fd, char **line)
{
	static	t_list		*stock;
	char				buf[BUFF_SIZE + 1];
	int					ret;
	int					result;

	if (BUFF_SIZE <= 0)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) != 0)
	{
		if (ret < 0 || fd < 0 || line == NULL)
			return (-1);
		buf[ret] = '\0';
		if ((result = ft_check(fd, buf, &stock)) == 1)
		{
			*line = ft_get(fd, &stock);
			return (1);
		}
		if (result == -1)
			return (-1);
	}
	if ((*line = ft_get(fd, &stock)) != NULL)
		return (1);
	return (0);
}
