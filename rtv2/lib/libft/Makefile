# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchaillo <vchaillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 15:04:37 by vchaillo          #+#    #+#              #
#    Updated: 2015/02/17 08:46:37 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC	=	gcc
CFLAGS	+=	-Wall -Wextra -Werror -g
RM	=	rm -Rf

SRC =  ft_strlen.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putendl.c\
	   ft_strclr.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c\
	   ft_strncat.c ft_strcmp.c ft_strstr.c ft_strchr.c ft_isalpha.c\
	   ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_tolower.c\
	   ft_toupper.c ft_atoi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c\
	   ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c\
	   ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c\
	   ft_memmove.c ft_memcmp.c ft_strlcat.c ft_memalloc.c ft_memdel.c\
	   ft_strnew.c ft_strdel.c ft_strequ.c ft_strnequ.c ft_strsub.c\
	   ft_strjoin.c ft_strtrim.c ft_striter.c ft_striteri.c ft_strmap.c\
	   ft_strmapi.c ft_itoa.c ft_strsplit.c ft_lstnew.c ft_lstdelone.c\
	   ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c get_next_line.c

INC = -I include

OBJ	=	$(patsubst %.c, obj/%.o, $(SRC))


all: $(NAME)
$(NAME): obj $(OBJ)
	@echo "[\033[1;32m******  Creating $@  ******\033[m]"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "[\033[1;32m√\033[m]" $<

obj:
	@mkdir -p obj

clean:
	@echo "[\033[31;1m******  Cleaning object files  ******\033[0m]"
	@$(RM) obj/

fclean:	clean
	@echo "[\033[31;1m******  Cleaning libft.a  ******\033[0m]"
	@$(RM) $(NAME)

norm:
	@echo "[\033[1;32m******  norminette ...  ******\033[0m]"
	@norminette **/*.[ch]

re: fclean all

.PHONY: all obj clean fclean norm re
