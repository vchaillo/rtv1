# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/06 22:40:14 by vchaillo          #+#    #+#              #
#    Updated: 2016/11/26 16:10:41 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	rtv1

CC	=	gcc
CFLAGS	+=	-Wall -Wextra -Werror
RM	=	rm -Rf

SRC	= 	main.c \
		mlx.c\
		key_hook.c\
		mouse_hook.c\
		draw.c\
		init.c\
		vector.c\
		raytracer.c\
		light.c\
		sphere.c\
		plane.c\
		cylinder.c\
		color.c\
		solve_equations.c\
		error.c\
		t_vector.c\
		t_scene.c\
		t_camera.c\
		t_sphere.c\
		t_plane.c\
		t_cylinder.c\
		t_object.c\
		t_light.c\
		t_color.c\

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIBMLX	=	-Llib/minilibx -lmlx -L/usr/lib -lXext -lX11 -lm
else
	UNAME_S = MACOS
	LIBMLX		=	-Llib/minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
endif

FILE := $(shell ls lib/libft/libft.a 2> /dev/null)

LIBFT =	 -Llib/libft/ -lft

INC	=	-I inc/ -I lib/minilibx/ -I lib/libft/include/

OBJ	=	$(patsubst %.c, obj/%.o, $(SRC))

all:   $(NAME)
$(NAME): obj $(OBJ)

ifneq ($(FILE), lib/libft/libft.a)
		@make -C lib/libft/ > /dev/null
endif

		@echo "[\033[1;34m******  Creating $(UNAME_S) executable  ******\033[m]"
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
		@echo "[\033[1;34m******  Norminette  ******\033[0m]"
		@norminette inc/*.h src/*.c

re: fclean all

.PHONY: all obj clean fclean norm re
