INC_PATH = ../include
LIB_PATH = ..
BUILD_PATH = obj
SRC_PATH = src

SOURCES = main.c test_malloc.c test_realloc.c test_mixed.c test_limit.c
LIB_SOURCES = -L.. -lft_malloc

OBJECTS = $(SOURCES:%.c=$(BUILD_PATH)/%.o)

NAME = test

CC = gcc

FLAGS_CC = -g3 # -Wall -Wextra -Werror

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIB_PATH)
	$(CC) $(FLAGS_CC) -o $@ $^ $(LIB_SOURCES)
	@echo "Compilation successful"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS_CC) -c -o $@ $< -I $(INC_PATH)

clean:
	@make clean -C $(LIB_PATH)
	@rm -rf $(BUILD_PATH)
	@echo "Clean \033[33mok\033[0m"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -f $(NAME) $(LIB_NAME)
	@echo "Fclean \033[33mok\033[0m"

re: fclean $(NAME)
