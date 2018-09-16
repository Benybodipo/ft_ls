# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besteba <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/27 09:18:47 by besteba           #+#    #+#              #
#    Updated: 2018/08/27 09:18:51 by besteba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

INC = -I includes/

UTILS = ft_itoa_base.c ft_strcmp.c ft_strlen.c

CORE =	

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
