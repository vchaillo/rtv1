# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 15:04:37 by vchaillo          #+#    #+#              #
#    Updated: 2016/12/23 14:37:33 by valentinchaillou89###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC	=	gcc
CFLAGS	+=	-Wall -Wextra -Werror -g
RM	=	rm -Rf

# Colors
NO_COLOR =		\033[0m
OK_COLOR =		\033[32;1m
KO_COLOR =		\033[31;1m
WARN_COLOR =	\033[34;1m
SILENT_COLOR =	\033[30;1m

# Directories
SRC_FOLDER = srcs/
OBJ_FOLDER = obj/

# Sources files
SRC_STRING = \
		string/ft_strlen.c\
		string/ft_strcpy.c\
		string/ft_strncpy.c\
		string/ft_strcat.c\
		string/ft_strncat.c\
		string/ft_strcmp.c\
		string/ft_strncmp.c\
		string/ft_strnstr.c\
		string/ft_strchr.c\
		string/ft_strrchr.c\
		string/ft_strclr.c\
		string/ft_strdup.c\
		string/ft_strnew.c\
		string/ft_strdel.c\
		string/ft_strequ.c\
		string/ft_strnequ.c\
		string/ft_strsub.c\
		string/ft_strjoin.c\
		string/ft_strtrim.c\
		string/ft_striter.c\
		string/ft_striteri.c\
		string/ft_strmap.c\
		string/ft_strmapi.c\
		string/ft_strlcat.c\
		string/ft_strsplit.c\
		string/ft_strstr.c\
		string/ft_isalpha.c\
		string/ft_isdigit.c\
		string/ft_isalnum.c\
		string/ft_isascii.c\
		string/ft_isprint.c\

SRC_MEMORY = \
		memory/ft_memset.c\
		memory/ft_bzero.c\
		memory/ft_memcpy.c\
		memory/ft_memccpy.c\
		memory/ft_memchr.c\
		memory/ft_memmove.c\
		memory/ft_memcmp.c\
		memory/ft_memalloc.c\
		memory/ft_memdel.c\

SRC_PRINT = \
		print/ft_putchar.c\
		print/ft_putendl.c\
		print/ft_putstr.c\
		print/ft_putnbr.c\
		print/ft_putfloat2.c\
		print/ft_putchar_fd.c\
		print/ft_putstr_fd.c\
		print/ft_putnbr_fd.c\
		print/ft_putendl_fd.c\

SRC_CONVERT = \
		convert/ft_tolower.c\
		convert/ft_toupper.c\
		convert/ft_atoi.c\
		convert/ft_itoa.c\

SRC_LIST = \
		list/ft_lstnew.c\
		list/ft_lstdelone.c\
		list/ft_lstdel.c\
		list/ft_lstadd.c\
		list/ft_lstiter.c\
		list/ft_lstmap.c\

SRC_GNL = \
		get_next_line.c\

SRC = $(SRC_STRING) $(SRC_MEMORY) $(SRC_PRINT) $(SRC_CONVERT) $(SRC_LIST) $(SRC_GNL)

# Objects files
OBJ = $(SRC:.c=.o)
OBJ := $(subst /,__,$(OBJ))
OBJ := $(addprefix $(OBJ_FOLDER), $(OBJ))
SRC := $(addprefix $(SRC_FOLDER),$(SRC))

INC = -I includes

# Rules
all: $(NAME)

$(OBJ_FOLDER)%.o:
		@mkdir -p $(OBJ_FOLDER)
		@$(CC) -c $(subst .o,.c,$(subst $(OBJ_FOLDER),$(SRC_FOLDER),$(subst __,/,$@))) $(INC) $(CFLAGS) $(MACROS) -o $@
		@printf "[$(OK_COLOR)√$(NO_COLOR)] "
		@echo "$(subst .o,.c,$(subst $(OBJ_FOLDER),$(SRC_FOLDER),$(subst __,/,$@)))"

$(NAME): $(OBJ)
		@echo "==========================="
		@printf "$(WARN_COLOR)Creating $(NAME)... $(NO_COLOR)"
		@ar rc $(NAME) $(OBJ)
		@ranlib $(NAME)
		@echo "$(OK_COLOR)Done √$(NO_COLOR)"
		@echo "==========================="

clean:
		@$(RM) $(OBJ)
		@$(RM) $(OBJ_FOLDER)
		@echo "$(WARN_COLOR)libft$(SILENT_COLOR) - Cleaning object files$(NO_COLOR)"

fclean:	clean
		@echo "$(WARN_COLOR)libft$(SILENT_COLOR) - Cleaning library$(NO_COLOR)"
		@$(RM) $(NAME)

norm:
		@echo "$(WARN_COLORNorminette...$(NO_COLOR)"
		@norminette **/*.[ch]

re: fclean all

.PHONY: all obj clean fclean norm re
