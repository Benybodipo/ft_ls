# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besteba <besteba@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/27 09:18:47 by besteba           #+#    #+#              #
#    Updated: 2018/09/20 13:03:38 by besteba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftls.a

FLAGS = -Wall -Wextra -Werror

INC = -I includes/

UTILS = ft_itoa_base.c ft_putstr.c ft_strcmp.c get_int_len.c print_3params.c \
		ft_putchar.c ft_str_append.c ft_strlen.c padding_left.c \

CORE = ft_ls.c handle_list.c sort.c getters.c handle_printing.c \
		resetters.c handle_errors.c  helpers.c setters.c \

COMP = $(addprefix ./core/, $(CORE)) $(addprefix ./utils/, $(UTILS))

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -c $(COMP) $(INC)
	@ar rc $(NAME) *.o
	@ranlib $(NAME)
clean:
		@rm -fr *.o

fclean: clean
		@rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean
