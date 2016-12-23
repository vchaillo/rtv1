# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/06 22:40:14 by vchaillo          #+#    #+#              #
#    Updated: 2016/12/23 16:23:33 by valentinchaillou89###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	rtv1

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM	=	rm -Rf

# Colors
NO_COLOR =		\033[0m
OK_COLOR =		\033[32;1m
KO_COLOR =		\033[31;1m
WARN_COLOR =	\033[34;1m
SILENT_COLOR =	\033[30;1m

# Directories
SRC_FOLDER = src/
OBJ_FOLDER = obj/

# Sources files
SRC_MAIN = \
		main.c\
		init.c\
		error.c\

SRC_CORE = \
		core/raytracer.c\
		core/light.c\
		core/plane.c\
		core/sphere.c\
		core/cylinder.c\

SRC_GUI = \
		gui/mlx.c\
		gui/draw.c\
		gui/key_hook.c\
		gui/mouse_hook.c\

SRC_CLI = \
		cli/output.c\
		cli/hooks_output.c\
		cli/objects_output.c\
		cli/lights_output.c\
		cli/tools_output.c\

SRC_TOOLS = \
		tools/vector.c\
		tools/solve_equations.c\
		tools/color.c\

SRC_STRUCTS = \
		structs/t_vector.c\
		structs/t_scene.c\
		structs/t_camera.c\
		structs/t_sphere.c\
		structs/t_plane.c\
		structs/t_cylinder.c\
		structs/t_object.c\
		structs/t_light.c\
		structs/t_color.c\

SRC = $(SRC_MAIN) $(SRC_CORE) $(SRC_GUI) $(SRC_CLI) $(SRC_TOOLS) $(SRC_STRUCTS)

# Objects files
OBJ = $(SRC:.c=.o)
OBJ := $(subst /,__,$(OBJ))
OBJ := $(addprefix $(OBJ_FOLDER), $(OBJ))
SRC := $(addprefix $(SRC_FOLDER),$(SRC))

# Inludes and libraries
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
LIBMLX	=	-Llib/minilibx -lmlx -L/usr/lib -lXext -lX11 -lm
else
UNAME_S = MACOS
LIBMLX		=	-Llib/minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
endif
LIBFT =	 -Llib/libft/ -lft
INC	=	-I inc/ -I lib/minilibx/ -I lib/libft/includes/

# Rules
all:	libft $(NAME)

$(OBJ_FOLDER)%.o:
		@mkdir -p $(OBJ_FOLDER)
		@$(CC) -c $(subst .o,.c,$(subst $(OBJ_FOLDER),$(SRC_FOLDER),$(subst __,/,$@))) $(INC) $(CFLAGS) $(MACROS) -o $@
		@printf "[$(OK_COLOR)√$(NO_COLOR)] "
		@echo "$(subst .o,.c,$(subst $(OBJ_FOLDER),$(SRC_FOLDER),$(subst __,/,$@)))"

$(NAME): $(OBJ)
		@echo "========================================="
		@printf "$(WARN_COLOR)Creating $(UNAME_S) $(NAME) executable... $(NO_COLOR)"
		@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBMLX) $(LIBFT)
		@echo "$(OK_COLOR)Done √$(NO_COLOR)"
		@echo "========================================="

libft:
		@make -C lib/libft/ 2>&-

clean:
		@$(RM) $(OBJ)
		@$(RM) $(OBJ_FOLDER)
		@echo "$(WARN_COLOR)$(NAME)$(SILENT_COLOR) - Cleaning object files$(NO_COLOR)"

fclean:	clean
		@$(RM) $(NAME)
		@echo "$(WARN_COLOR)$(NAME)$(SILENT_COLOR) - Cleaning executables$(NO_COLOR)"
		@make -C lib/libft/ fclean 2>&-

norm:
		@echo "$(WARN_COLORNorminette...$(NO_COLOR)"
		@norminette inc/*.h src/*.c

re: fclean all

.PHONY: all obj libft clean fclean norm re
