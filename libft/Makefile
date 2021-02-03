# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabelque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/22 12:03:18 by aabelque          #+#    #+#              #
#    Updated: 2021/02/03 18:07:53 by aabelque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC = ft_atoi.c ft_bzero.c ft_factorial.c ft_isalnum.c ft_isalpha.c \
	  ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c \
	  ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c \
	  ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	  ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
	  ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_strjoin2.c \
	  ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_sqrt.c ft_strcat.c \
	  ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c \
	  ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
	  ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
	  ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
	  ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c \
	  ft_swap.c ft_tolower.c ft_toupper.c get_msg.c ft_add_endlist.c \
	  ft_nb_elemlist.c  ft_pushback_list.c ft_add_list.c epur_str.c \
	  ft_rm_endlist.c ft_rm_frontlist.c ft_rmlist.c get_next_line.c \
	  ft_itoa_base.c ft_atoi_base.c ft_printlist.c ft_len_number.c \
	  ft_memcharcpy.c ft_lltoa.c ft_ulltoa.c ft_utoa.c ft_len_unumber.c \
	  ft_utoa_base.c ft_itoa_base_uppercase.c ft_lltoa_base.c \
	  ft_atoll_base.c ft_putlnbr.c

INCDIR = include/
INCFILE = libft.h
INC = $(addprefix $(INCDIR),$(INCFILE))

SRC_DIR = srcs/

OBJ_DIR = objs/

HEADERS = -Ilibft.h

MKDIR = mkdir -p

OBJ = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

all: print $(NAME)

print:
	@echo "\033[32m[\c"

$(NAME): $(OBJ_DIR) $(OBJ) $(INC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@tput dl; tput el1; tput cub 100; echo "\033[33mBuilt library:\033[0m \033[32;1;4m$(notdir $@)\033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@$(CC) -fPIC $(CFLAGS) -I$(INCDIR) -o $@ -c $<
	@tput dl; tput el1; tput cub 100; echo "\033[33mCreating object files: \033[32;1;4m$(notdir $@)\033[0m\c"

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

norme:
	@norminette $(SRC_DIR)
	@echo "\033[3;32m[ ✔ ] Norme is done.\033[0m"

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@echo "\033[33mRemoved files: \033[32;1;4mObject files\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo "\033[33mRemoved library: \033[32;1;4m$(NAME)\033[0m"

re: fclean all

.PHONY: all clean fclean re
