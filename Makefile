# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 02:45:47 by mpivet-p          #+#    #+#              #
#    Updated: 2020/10/03 14:09:37 by mpivet-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE), $(NAME))
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME= libft_malloc.so
CC= gcc
CFLAGS= -Wall -Wextra -Werror -std=c90 -g

INC_PATH= includes/
SRC_PATH= srcs/
OBJ_PATH= obj/

INC_NAME= libft_malloc.h
SRC_NAME= malloc.c #free.c realloc.c show_alloc_mem.c
OBJ_NAME= $(SRC_NAME:.c=.o)

INC= -I includes/ -I libft/inc/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIBS= -L libft/ -lft

.PHONY: all clean fclean re local

all: $(NAME)
	@:

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJ) $(INC) $(LIBS)
	ln -sf libft_malloc.so libft_malloc_$(HOSTTYPE).so

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INC) -o $@ -c -fPIC $<

clean:
	@make -C libft clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME) libft_malloc_$(HOSTTYPE).so

re: fclean all
