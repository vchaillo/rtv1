NAME =	rtv2

CC	=	gcc
CFLAGS	+=	-Wall -Wextra -Werror
RM	=	rm -Rf

SRC	= 	main.c \
		mlx.c\
		draw.c\
		init.c\
		vector.c\
		raytracer.c\
		light.c\
		sphere.c\
		plane.c\
		color.c\
		error.c\
		t_vector.c\
		t_scene.c\
		t_camera.c\
		t_sphere.c\
		t_plane.c\
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
		@echo "[\033[1;32m******  norminette ...  ******\033[0m]"
		@norminette inc/*.[ch] src/*.[ch]

re: fclean all

.PHONY: all obj clean fclean norm re
