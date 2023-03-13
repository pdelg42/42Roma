# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 09:37:55 by aperrone          #+#    #+#              #
#    Updated: 2023/02/14 16:23:23 by aperrone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

MAIN = main.c
INC = includes/philo.h

SRCS = srcs/
LIBFT = libft/
LISTFT = listft/
FILES = *.c

FLAGS = -Wall -Wextra -Werror

OBJS = *.o

$(OBJS):
	gcc		$(FLAGS) $(MAIN) \
			$(SRCS)$(FILES) \
			-o $(NAME)

d:
	gcc		-g $(FLAGS) $(MAIN) \
			$(INC) \

$(NAME): 
	make $(OBJS)
	make clean

clean:
	rm -f $(OBJS)

fclean: 
	make clean
	rm -f $(NAME)

re:
	make fclean
	make

.PHONY: all clean fclean