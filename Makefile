# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besteba <besteba@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/27 09:18:47 by besteba           #+#    #+#              #
#    Updated: 2018/09/27 12:52:50 by besteba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

INC = -I includes/

UTILS = char_to_str.c ft_itoa_base.c ft_putchar.c ft_putstr.c ft_str_append.c \
		ft_strcmp.c ft_strlen.c get_int_len.c padding_left.c print_3params.c

SRCS = getters.c getters_2.c handle_errors.c handle_list.c \
		handle_printing.c helpers.c main.c resetters.c setters.c sort.c

COMP = $(addprefix srcs/, $(SRCS))
COMP2 = $(addprefix utils/, $(UTILS))


$(NAME):
	@gcc -o $(NAME) $(FLAGS) $(COMP) $(COMP2) $(INC)

all: $(NAME)

clean:
		@rm -fr *.o

fclean: clean
		@rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean
