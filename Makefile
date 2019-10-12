# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 18:27:31 by hcabel            #+#    #+#              #
#    Updated: 2019/10/12 17:54:05 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG				=	yes

ifeq ($(DEBUG), yes)
	FLAGS			=	-g
	COLOR			=	\033[31m
else
	FLAGS			=	-Wall -Wextra -Werror
	COLOR			=	\033[32m
endif

NAME				=	libftprintf.a

NAME_FOLDER_OBJECT 	= 	objects

PATH_SOURCES		=	srcs/
PATH_INCLUDE		=	includes/

PATH_OBJECT			=	$(NAME_FOLDER_OBJECT)/

PATH_STR			=	$(PATH_SOURCES)str/
PATH_LST			=	$(PATH_SOURCES)lst/
PATH_PUT			=	$(PATH_SOURCES)put/
PATH_IS				=	$(PATH_SOURCES)is/
PATH_MEM			=	$(PATH_SOURCES)mem/
PATH_PRINTF			=	$(PATH_SOURCES)printf/
PATH_OTHER			=	$(PATH_SOURCES)others/

_GRAS				=	\033[1m
_FADE				=	\033[2m
_ITALIQUE			=	\033[3m
_SOUSLIGNER			=	\033[4m
_BLACK				=	\033[30m
_RED				=	\033[31m
_GREEN				=	\033[32m
_YELLOW				=	\033[33m
_BLUE				=	\033[34m
_VIOLET				=	\033[35m
_CYAN				=	\033[36m
_WHITE				=	\033[37m
_END				=	\033[0m
OK_COLOR			=	\x1b[32;01m
WARN_COLOR			=	\x1b[33;01m
ERROR_COLOR			=	\x1b[31;01m

LIST_STR			=	ft_strlen.c		\
						ft_strdup.c		\
						ft_strcpy.c		\
						ft_strncpy.c	\
						ft_strcat.c		\
						ft_strncat.c	\
						ft_strlcat.c	\
						ft_strchr.c		\
						ft_strrchr.c	\
						ft_strstr.c		\
						ft_strnstr.c	\
						ft_strcmp.c		\
						ft_strncmp.c	\
						ft_strnew.c		\
						ft_strdel.c		\
						ft_strclr.c		\
						ft_striter.c	\
						ft_striteri.c	\
						ft_strmap.c		\
						ft_strmapi.c	\
						ft_strequ.c		\
						ft_strnequ.c	\
						ft_strsub.c		\
						ft_strjoin.c	\
						ft_strtrim.c	\
						ft_strsplit.c	\
						ft_strndup.c

LIST_LST			=	ft_lstnew.c		\
						ft_lstdelone.c	\
						ft_lstdel.c		\
						ft_lstadd.c		\
						ft_lstiter.c	\
						ft_lstmap.c

LIST_PUT			=	ft_putchar.c	\
						ft_putstr.c		\
						ft_putendl.c	\
						ft_putnbr.c		\
						ft_putchar_fd.c	\
						ft_putstr_fd.c	\
						ft_putendl_fd.c	\
						ft_putnbr_fd.c

LIST_OTHER			=	ft_bzero.c		\
						ft_atoi.c		\
						ft_atoi_base.c	\
						ft_toupper.c	\
						ft_tolower.c	\
						ft_itoa.c		\
						ft_sqrt.c		\
						ft_baselen.c	\
						ft_itoa_base.c	\
						ft_nbrlen.c		\
						get_next_line.c	\
						ft_convert_base.c

LIST_IS				=	ft_isalpha.c	\
						ft_isdigit.c	\
						ft_isalnum.c	\
						ft_isascii.c	\
						ft_isprint.c	\
						ft_is_prime.c

LIST_MEM			=	ft_memset.c		\
						ft_memcpy.c		\
						ft_memccpy.c	\
						ft_memmove.c	\
						ft_memchr.c		\
						ft_memcmp.c		\
						ft_memalloc.c	\
						ft_memdel.c

LIST_PRINTF			=	colour.c			\
						ft_printf.c			\
						pf_dispatch.c		\
						pf_parse_flags.c	\
						ft_ftoa.c			\
						get_variable.c		\
						pf_modify_value.c	\
						utils.c				\
											\
						flags_c.c			\
						flags_s.c			\
						flags_p.c			\
						flags_d.c			\
						flags_o.c			\
						flags_x.c			\
						flags_x2.c			\
						flags_u.c

SOURCES				=	$(addprefix $(PATH_STR), $(LIST_STR))		\
						$(addprefix $(PATH_LST), $(LIST_LST))		\
						$(addprefix $(PATH_PUT), $(LIST_PUT))		\
						$(addprefix $(PATH_OTHER), $(LIST_OTHER))	\
						$(addprefix $(PATH_IS), $(LIST_IS))			\
						$(addprefix $(PATH_PRINTF), $(LIST_PRINTF))	\
						$(addprefix $(PATH_MEM), $(LIST_MEM))

OBJECTS				=	$(addprefix $(PATH_OBJECT), $(LIST_STR:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_LST:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_PUT:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_OTHER:.c=.o))	\
						$(addprefix $(PATH_OBJECT), $(LIST_IS:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_PRINTF:.c=.o))	\
						$(addprefix $(PATH_OBJECT), $(LIST_MEM:.c=.o))

INCLUDES			=	$(addprefix -I, $(PATH_INCLUDE))

START				=	1
PRC					=	0

.PHONY:		re clean fclean all norme refclean design
.SILENT:	re fclean clean all norme refclean design \
				$(NAME) $(OBJECTS) $(NAME_FOLDER_OBJECT)

all: design $(NAME)
	if [[ $(DEBUG) == yes ]]; then echo "\n$(_BLUE)        <==========|$(ERROR_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; \
	else echo "\n$(_BLUE)        <==========|$(OK_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; fi

design:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)

$(NAME): $(NAME_FOLDER_OBJECT) $(OBJECTS)
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

$(PATH_OBJECT)%.o: $(PATH_STR)%.c
	$(eval PRC = $(shell echo "$(PRC) + 1" | bc -l))
	printf "\r$(_VIOLET)[$(_GRAS)%3.f%%$(_END)$(_VIOLET)] $(_CYAN)[> $(COLOR)$(_GRAS)%-17s%17s$(_END)$(_CYAN) <]\t" \
	$(shell echo "100 / $(words $(SOURCES)) * $(PRC)" | bc -l) $(shell echo $@ | cut -d '/' -f2)  $(shell echo $< | cut -d '/' -f3)
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_LST)%.c
	$(eval PRC = $(shell echo "$(PRC) + 1" | bc -l))
	printf "\r$(_VIOLET)[$(_GRAS)%3.f%%$(_END)$(_VIOLET)] $(_CYAN)[> $(COLOR)$(_GRAS)%-17s%17s$(_END)$(_CYAN) <]\t" \
	$(shell echo "100 / $(words $(SOURCES)) * $(PRC)" | bc -l) $(shell echo $@ | cut -d '/' -f2)  $(shell echo $< | cut -d '/' -f3)
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_PUT)%.c
	$(eval PRC = $(shell echo "$(PRC) + 1" | bc -l))
	printf "\r$(_VIOLET)[$(_GRAS)%3.f%%$(_END)$(_VIOLET)] $(_CYAN)[> $(COLOR)$(_GRAS)%-17s%17s$(_END)$(_CYAN) <]\t" \
	$(shell echo "100 / $(words $(SOURCES)) * $(PRC)" | bc -l) $(shell echo $@ | cut -d '/' -f2)  $(shell echo $< | cut -d '/' -f3)
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_IS)%.c
	$(eval PRC = $(shell echo "$(PRC) + 1" | bc -l))
	printf "\r$(_VIOLET)[$(_GRAS)%3.f%%$(_END)$(_VIOLET)] $(_CYAN)[> $(COLOR)$(_GRAS)%-17s%17s$(_END)$(_CYAN) <]\t" \
	$(shell echo "100 / $(words $(SOURCES)) * $(PRC)" | bc -l) $(shell echo $@ | cut -d '/' -f2)  $(shell echo $< | cut -d '/' -f3)
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_MEM)%.c
	$(eval PRC = $(shell echo "$(PRC) + 1" | bc -l))
	printf "\r$(_VIOLET)[$(_GRAS)%3.f%%$(_END)$(_VIOLET)] $(_CYAN)[> $(COLOR)$(_GRAS)%-17s%17s$(_END)$(_CYAN) <]\t" \
	$(shell echo "100 / $(words $(SOURCES)) * $(PRC)" | bc -l) $(shell echo $@ | cut -d '/' -f2)  $(shell echo $< | cut -d '/' -f3)
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_OTHER)%.c
	$(eval PRC = $(shell echo "$(PRC) + 1" | bc -l))
	printf "\r$(_VIOLET)[$(_GRAS)%3.f%%$(_END)$(_VIOLET)] $(_CYAN)[> $(COLOR)$(_GRAS)%-17s%17s$(_END)$(_CYAN) <]\t" \
	$(shell echo "100 / $(words $(SOURCES)) * $(PRC)" | bc -l) $(shell echo $@ | cut -d '/' -f2)  $(shell echo $< | cut -d '/' -f3)
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_PRINTF)%.c
	$(eval PRC = $(shell echo "$(PRC) + 1" | bc -l))
	printf "\r$(_VIOLET)[$(_GRAS)%3.f%%$(_END)$(_VIOLET)] $(_CYAN)[> $(COLOR)$(_GRAS)%-17s%17s$(_END)$(_CYAN) <]\t" \
	$(shell echo "100 / $(words $(SOURCES)) * $(PRC)" | bc -l) $(shell echo $@ | cut -d '/' -f2)  $(shell echo $< | cut -d '/' -f3)
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(NAME_FOLDER_OBJECT):
	mkdir -p $(NAME_FOLDER_OBJECT)

clean:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME_FOLDER_OBJECT)"
	rm -rf $(NAME_FOLDER_OBJECT)
	if [[ $(DEBUG) == yes ]]; then echo "$(_BLUE)        <==========|$(ERROR_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; \
	else echo "$(_BLUE)        <==========|$(OK_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; fi

fclean:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME)$(_END)"
	rm -f $(NAME)
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME_FOLDER_OBJECT)$(_END)"
	rm -rf $(NAME_FOLDER_OBJECT)
	if [[ $(DEBUG) == yes ]]; then echo "$(_BLUE)        <==========|$(ERROR_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; \
	else echo "$(_BLUE)        <==========|$(OK_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; fi

refclean:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME)$(_END)"
	rm -f $(NAME)
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME_FOLDER_OBJECT)$(_END)"
	rm -rf $(NAME_FOLDER_OBJECT)

re: refclean all

norme:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <===============|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|===============>$(_VIOLET)$(_ITALIQUE)"; fi
	$(eval START = 0)
	norminette $(SOURCES)
	if [[ $(DEBUG) == yes ]]; then echo "$(_BLUE)        <==========|$(ERROR_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; \
	else echo "$(_BLUE)        <==========|$(OK_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; fi

