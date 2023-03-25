# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 12:30:45 by aperrone          #+#    #+#              #
#    Updated: 2023/03/25 09:10:21 by aperrone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ECHO = echo
ENV = env
PWD = pwd
FILES = *.c
LIBSRCS = ../srcs/libft/*.c

OBJS = *.o

all :
	@gcc $(LIBSRCS) echo.c -o $(ECHO)
	bash ../srcs/libft/_piggy
	bash ../srcs/libft/_piggy0
	@afplay -v 0.5 '../srcs/libft/??.mp3'
	@gcc env.c -o $(ENV)
	@gcc pwd.c -o $(PWD)
	
clean:
	@rm -f $(OBJS)

fclean: 
	@make clean
	@rm -f $(ECHO)
	@rm -f $(CD)
	@rm -f $(ENV)
	@rm -f $(PWD)