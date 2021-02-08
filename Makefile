# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azziz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 10:06:32 by azziz             #+#    #+#              #
#    Updated: 2021/02/08 17:16:35 by aabelque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

H_DIR = include/
C_DIR = srcs/
O_DIR = objs/

NAME = libft_malloc.so
NNAME = libft_malloc

CC = gcc
DEBUG = -g3
CFLAG = -Wall -Wextra -Werror -Wpadded

SRC = malloc.c \
	  free.c \
	  utils.c \
	  show_alloc_mem.c \
	  realloc.c \
	  calloc.c \
	  libft.c

OBJS = $(addprefix $(O_DIR),$(SRC:.c=.o))

all: $(NAME)
	
$(NAME): $(OBJS)
	@$(CC) $(DEBUG) -shared -o $(NNAME)_$(HOSTTYPE).so $(OBJS)
	@ar rc malloc.a $(OBJS)
	@ranlib malloc.a
	@rm -rf $(NAME)
	@ln -sf $(NNAME)_$(HOSTTYPE).so $(NAME)
	@tput dl; tput el1; tput cub 100; echo "\033[33mBuilt library:\033[0m \033[32;1;4m$(notdir $@)\033[0m"

$(OBJS): $(O_DIR)%.o: $(C_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $< -fPIC -I$(H_DIR)

norme:
	@norminette $(C_DIR)
	@norminette $(H_DIR)
	@echo "\033[3;32m[ ✔ ] Norme is done.\033[0m"

clean:
	@rm -rf $(O_DIR) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -rf malloc.a 2> /dev/null || echo "" > /dev/null
	@rm -rf $(NAME) 2> /dev/null || echo "" > /dev/null
	@rm -rf $(NNAME)_$(HOSTTYPE).so 2> /dev/null || echo "" > /dev/null
	@echo "\033[33mRemoved library: \033[32;1;4m$(NAME)\033[0m"
	@echo "\033[33mRemoved library: \033[32;1;4m$(NNAME)_$(HOSTTYPE).so\033[0m"

re: fclean all

.PHONY: all clean fclean re
