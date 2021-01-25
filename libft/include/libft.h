/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:54:05 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/22 15:11:39 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFF_SIZE 4096

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <wchar.h>
# include <inttypes.h>

typedef struct		s_list
{
	char			*str;
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	int				fd;
}					t_list;

char				*ft_utoa_base(unsigned int n,
        unsigned int base);
char				*ft_utoa(unsigned int n);
char				*ft_ulltoa(unsigned long long n);
char				*ft_lltoa(long long n);
char                *ft_lltoa_base(long long val, int base);
void				*ft_memcharcpy(void *dest, const char c, size_t n);
int					ft_len_number(int n);
int					ft_len_unumber(unsigned int n);
char				*ft_itoa_base(int val, int base);
char				*ft_itoa_base_uppercase(int val, int base);
int					ft_atoi_base(const char *str, int str_base);
void				epur_str(char *str);
int					get_next_line(const int fd, char **line);
void				ft_putwchar(wchar_t c);
void				ft_pushback_list(t_list **alst, t_list *new);
void				ft_add_endlist(t_list **list, char *str);
void				ft_add_list(t_list **list, char *str);
int					ft_nb_elemlist(t_list *list);
void				ft_printlist(t_list *list);
void				ft_rm_endlist(t_list **list);
void				ft_rm_frontlist(t_list **list);
void				ft_rmlist(t_list **list);
void				get_msg(char *str);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
char				*ft_itoa(int n);
char				**ft_strsplit(char const *s, char c);
char				*ft_strtrim(char const *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin2(char const *s1, char const *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strmap(char const *s, char (*f)(char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_striter(char *s, void (*f)(char *));
void				ft_strclr(char *s);
void				*ft_memalloc(size_t size);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_strnew(size_t size);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				ft_strdel(char **as);
void				ft_memdel(void **ap);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_swap(int *a, int *b);
size_t				ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isspace(int c);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_factorial(int nb);
int					ft_sqrt(int nb);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strdup(const char *s);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
#endif
