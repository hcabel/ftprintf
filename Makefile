# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/21 11:09:36 by hcabel            #+#    #+#              #
#    Updated: 2019/10/06 17:29:47 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG			=	no
DL				=	yes

ifeq ($(DEBUG), yes)
	MSG			=	echo "\033[0;31m/!\\ Warning /!\\ \
						\033[0;36mDebug mode ON\033[0;35m"
	FLAGS		=	-g
else
	FLAGS		=	-Wall -Wextra -Werror
endif

ifeq (, $(wildcard libft))
ifeq ($(DL), yes)
	UPDATE		=	git clone https://github.com/hcabel/libft.git libft \
						&& echo '\n'
else
	UPDATE		=	echo "\033[0;31m/!\\ Warning /!\\ \033[0;36m DL is \
						off \n But you can add your libft\033[0;35m"
endif
endif

ifeq (, $(wildcard libft/libft.a))
	CHECK		=	make -C libft
endif

NAME			=	libftprintf.a

OBJECT_REP		=	objects
INCLUDE_REP		=	includes
SOURCES_REP		=	srcs

INCLUDES_FILE	=	ft_printf.h

SRCS			=	ft_printf.c			\
					pf_dispatch.c		\
					pf_parse_flags.c	\
					pf_modify_value.c	\
					colour.c			\
					get_variable.c		\
					ft_ftoa.c			\
					utils.c

OBJECTS_LIBFT	=	libft/objects/ft_atoi.o			\
					libft/objects/ft_atoi_base.o	\
					libft/objects/ft_baselen.o		\
					libft/objects/ft_bzero.o		\
					libft/objects/ft_convert_base.o	\
					libft/objects/ft_is_prime.o		\
					libft/objects/ft_isalnum.o		\
					libft/objects/ft_isalpha.o		\
					libft/objects/ft_isascii.o		\
					libft/objects/ft_isdigit.o		\
					libft/objects/ft_isprint.o		\
					libft/objects/ft_itoa.o			\
					libft/objects/ft_itoa_base.o	\
					libft/objects/ft_lstadd.o		\
					libft/objects/ft_lstdel.o		\
					libft/objects/ft_lstdelone.o	\
					libft/objects/ft_lstiter.o		\
					libft/objects/ft_lstmap.o		\
					libft/objects/ft_lstnew.o		\
					libft/objects/ft_memalloc.o		\
					libft/objects/ft_memccpy.o		\
					libft/objects/ft_memchr.o		\
					libft/objects/ft_memcmp.o		\
					libft/objects/ft_memcpy.o		\
					libft/objects/ft_memdel.o		\
					libft/objects/ft_memmove.o		\
					libft/objects/ft_memset.o		\
					libft/objects/ft_nbrlen.o		\
					libft/objects/ft_putchar.o		\
					libft/objects/ft_putchar_fd.o	\
					libft/objects/ft_putendl.o		\
					libft/objects/ft_putendl_fd.o	\
					libft/objects/ft_putnbr.o		\
					libft/objects/ft_putnbr_fd.o	\
					libft/objects/ft_putstr.o		\
					libft/objects/ft_putstr_fd.o	\
					libft/objects/ft_sqrt.o			\
					libft/objects/ft_strcat.o		\
					libft/objects/ft_strchr.o		\
					libft/objects/ft_strclr.o		\
					libft/objects/ft_strcmp.o		\
					libft/objects/ft_strcpy.o		\
					libft/objects/ft_strdel.o		\
					libft/objects/ft_strdup.o		\
					libft/objects/ft_strequ.o		\
					libft/objects/ft_striter.o		\
					libft/objects/ft_striteri.o		\
					libft/objects/ft_strjoin.o		\
					libft/objects/ft_strlcat.o		\
					libft/objects/ft_strlen.o		\
					libft/objects/ft_strmap.o		\
					libft/objects/ft_strmapi.o		\
					libft/objects/ft_strncat.o		\
					libft/objects/ft_strncmp.o		\
					libft/objects/ft_strncpy.o		\
					libft/objects/ft_strndup.o		\
					libft/objects/ft_strnequ.o		\
					libft/objects/ft_strnew.o		\
					libft/objects/ft_strnstr.o		\
					libft/objects/ft_strrchr.o		\
					libft/objects/ft_strsplit.o		\
					libft/objects/ft_strstr.o		\
					libft/objects/ft_strsub.o		\
					libft/objects/ft_strtrim.o		\
					libft/objects/ft_tolower.o		\
					libft/objects/ft_toupper.o		\
					libft/objects/get_next_line.o

INCLUDES		=	-I $(INCLUDE_REP)/ -I libft/$(INCLUDE_REP)

OBJECTS			=	$(addprefix $(OBJECT_REP)/, $(SRCS:.c=.o))

.PHONY: all clean fclean re mkdir make
.SILENT: all clean fclean re $(OBJECT_FILE) $(NAME) $(OBJECTS) mkdir make \
			remake update remove norm

all: update $(NAME)
	$(MSG)

$(NAME): mkdir make $(OBJECTS)
	echo "\n\033[0;36mCreate [$@]\n\033[0;35m"
	ar rc $(NAME) $(OBJECTS) $(OBJECTS_LIBFT)

mkdir:
	mkdir -p $(OBJECT_REP)

$(OBJECT_REP)/%.o: $(SOURCES_REP)/%.c $(INCLUDE_REP)/$(INCLUDES_FILE) Makefile
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]				\c"
	gcc $(FLAGS) -o $@ $(INCLUDES) -c $<

clean:
	rm -rf $(OBJECT_REP)

fclean: clean
	rm -f $(NAME)

re: remove fclean all

remove:
	make -C libft re

update:
	clear
	echo "\n\033[0;35mUpdate \033[0;32m[\033[0;33mlibft\033[0;32m]\033[0;35m\n"
	$(UPDATE)
	$(CHECK)

make:
	make -C libft

norm:
	norminette $(SOURCES_REP)
	norminette $(INCLUDE_REP)
