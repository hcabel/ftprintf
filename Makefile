# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sylewis <sylewis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/21 11:09:36 by hcabel            #+#    #+#              #
#    Updated: 2019/07/22 01:27:00 by sylewis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG			=	yes
DL				=	yes

ifeq ($(DEBUG), yes)
	MSG			=	echo "\033[0;31m/!\\ Warning /!\\ \
						\033[0;36mDebug mode ON\033[0;35m"
	FLAGS		=   -g
else
	FLAGS		=   -Wall -Wextra -Werror
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

NAME			=	printf

OBJECT_REP		=	objects
INCLUDE_REP		=	includes
SOURCES_REP		=	srcs

INCLUDES_FILE	=	ft_printf.h

SRCS			=	main.c				\
					ft_printf.c			\
					display.c			\
					dispatch.c			\
					get_variable.c		\
					utils.c				\
					ft_ftoa.c
				

INCLUDES		=	-I $(INCLUDE_REP)/ -I libft/$(INCLUDE_REP)

OBJECTS			=	$(addprefix $(OBJECT_REP)/, $(SRCS:.c=.o))

.PHONY: all clean fclean re mkdir make
.SILENT: all clean fclean re $(OBJECT_FILE) $(NAME) $(OBJECTS) mkdir make \
			remake update remove norm

all: update $(NAME)
	$(MSG)

$(NAME): mkdir make $(OBJECTS)
	echo "\n\033[0;36mCreate [$@]\n\033[0;35m"
	gcc $(FLAGS) -o $(NAME) $(OBJECTS) -L libft/ -lft

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
