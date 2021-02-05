/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:20:29 by azziz             #+#    #+#             */
/*   Updated: 2021/02/05 16:39:32 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libft/include/libft.h"
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>

# define PROT (PROT_READ | PROT_WRITE)
# define FLGS (MAP_ANON | MAP_PRIVATE)
# define PS getpagesize()
# define SMALL PS
# define TINY PS / 4
# define STRUCT(x) ft_getalign(sizeof(x), 16)
# define TINY_ZONE ((TINY + STRUCT(t_page) + STRUCT(t_block)) * 100)
# define SMALL_ZONE ((SMALL + STRUCT(t_page) + STRUCT(t_block)) * 100)
# define T 1
# define S 2
# define L 3

typedef struct	s_block
{
	short			free;
	size_t			len;
	void			*p;
	struct s_block	*nxt;
	struct s_block	*prv;
}				t_block;

typedef struct	s_page
{
	short			free;
	size_t			rest;
	size_t			size;
	t_block			*blk;
	struct s_page	*nxt;
}				t_page;

typedef struct	s_malloc
{
	t_page			*tiny;
	t_page			*small;
	t_page			*large;
}				t_malloc;

t_malloc			g_lst;

void			free(void *ptr);
void			*malloc(size_t size);
size_t			ft_getalign(size_t size, int align);
t_block			*ft_new_block(size_t size);
void			show_alloc_mem(void);
void			*ft_create_zone(t_page *prev, size_t size, size_t len);
void			*ft_alloc_large(t_page **page, size_t len);
void			ft_init_block(t_block **nw, t_block **blk, size_t len);
void			ft_can_i_free(t_page *zone);
void			*realloc(void *ptr, size_t size);
t_block			*ft_findblock(t_page **page, size_t sz);

#endif
