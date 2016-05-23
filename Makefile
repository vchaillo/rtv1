#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarbie <jbarbie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/20 18:44:07 by jbarbie           #+#    #+#              #
#    Updated: 2016/05/19 22:04:36 by vchaillo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	=	rtv1

CC	=	gcc
CFLAGS	+=	-Wall -Wextra -Werror
RM	=	rm -Rf

SRC	=	main.c \
		mlx.c\
		draw.c\

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIBMLX	=	-Lminilibx -lmlx -L/usr/lib -lXext -lX11 -lm
else
	LIBMLX		=	-Lminilibx_macos/ -lmlx -framework OpenGL -framework AppKit
endif

LIBFT		=	-Llibft/ -lft
LIBFT_LINUX	=	-Llibft/ -lft_linux

INC	=	-I inc/ -I minilibx/ -I libft/includes/

OBJ	=	$(patsubst %.c, obj/%.o, $(SRC))



all:   $(NAME)
$(NAME): obj $(OBJ)
		@echo "[\033[1;32m******  Creating $(UNAME_S) executable  ******\033[m]"
		@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBMLX) $(LIBFT)

obj/%.o: src/%.c
		@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
		@echo "[\033[1;32m√\033[m]" $<

obj:
		@mkdir -p obj

clean:
		@echo "[\033[31;1m******  Cleaning object files  ******\033[0m]"
		@$(RM) obj/

fclean:	clean
		@echo "[\033[31;1m******  Cleaning executables  ******\033[0m]"
		@$(RM) $(NAME)

norm:
		@echo "[\033[1;32m******  norminette...  ******\033[0m]"
		@norminette **/*.[ch]

re: fclean all

.PHONY: all linux obj clean fclean norm re