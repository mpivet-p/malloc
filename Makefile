# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 02:45:47 by mpivet-p          #+#    #+#              #
#    Updated: 2020/09/12 14:42:34 by mpivet-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE), $(NAME))
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME= libft_malloc.so
CC= gcc
CFLAGS= -Wall -Wextra -Werror -g

INC_PATH= includes/
SRC_PATH= srcs/
OBJ_PATH= obj/

INC_NAME= malloc.h
SRC_NAME= 
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
	ln -s libft_malloc.so libft_malloc_$(HOSTTYPE).so

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INC) -o $@ -c -fPIC $<

clean:
	@make -C libft clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME) server

re: fclean all