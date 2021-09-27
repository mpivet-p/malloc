# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 02:45:47 by mpivet-p          #+#    #+#              #
#    Updated: 2021/08/09 16:04:16 by mpivet-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE), $(NAME))
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME= libft_malloc.so
CC= clang
CFLAGS= -Wall -Wextra -Werror -std=gnu99 -g

INC_PATH= includes/
SRC_PATH= srcs/
OBJ_PATH= obj/

INC_NAME= libft_malloc.h
SRC_NAME= malloc.c free.c utils.c show_alloc_mem.c realloc.c calloc.c reallocarray.c printk.c
OBJ_NAME= $(SRC_NAME:.c=.o)

INC= -I includes/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all clean fclean re local

all: $(NAME)

$(NAME): $(OBJ)#-Wl,-soname,
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJ) $(INC)
	ln -sf libft_malloc.so libft_malloc_$(HOSTTYPE).so

test: $(OBJ)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) -o small_test small_test.c 
	@./small_test

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	$(CC) $(CFLAGS) -fpic $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH) small_test

fclean: clean
	@rm -rf $(NAME) libft_malloc_$(HOSTTYPE).so

re: fclean all
