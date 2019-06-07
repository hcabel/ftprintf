# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/21 11:09:36 by hcabel            #+#    #+#              #
#    Updated: 2019/06/07 10:23:32 by hcabel           ###   ########.fr        #
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
PARSING_REP		=	$(SOURCES_REP)/parsing
FUNCTION_REP	=	$(SOURCES_REP)/conversions
DISPLAY_REP		=	$(SOURCES_REP)/display

INCLUDES_FILE	=	ft_printf.h

PARSING_SRCS	=	parsing.c			\
					stock_variable.c	\
					stock_flags.c
					
FUNCTION_SRCS	=	ft_itoa_base.c

DISPLAY_SRCS	=	display.c			\
					show.c				\
					utils.c

OTHERS_SRCS		=	main.c				\
					ft_printf.c			

INCLUDES		=	-I $(INCLUDE_REP)/ -I libft/$(INCLUDE_REP)

OBJECTS			=	$(addprefix $(OBJECT_REP)/, $(PARSING_SRCS:.c=.o))	\
					$(addprefix $(OBJECT_REP)/, $(FUNCTION_SRCS:.c=.o))	\
					$(addprefix $(OBJECT_REP)/, $(OTHERS_SRCS:.c=.o))	\
					$(addprefix $(OBJECT_REP)/, $(DISPLAY_SRCS:.c=.o))	

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

$(OBJECT_REP)/%.o: $(PARSING_REP)/%.c $(INCLUDE_REP)/$(INCLUDES_FILE) Makefile
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]				\c"
	gcc $(FLAGS) -o $@ $(INCLUDES) -c $<

$(OBJECT_REP)/%.o: $(FUNCTION_REP)/%.c $(INCLUDE_REP)/$(INCLUDES_FILE) Makefile
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]				\c"
	gcc $(FLAGS) -o $@ $(INCLUDES) -c $<

$(OBJECT_REP)/%.o: $(DISPLAY_REP)/%.c $(INCLUDE_REP)/$(INCLUDES_FILE) Makefile
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