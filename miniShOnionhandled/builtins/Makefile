# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 12:30:45 by aperrone          #+#    #+#              #
#    Updated: 2023/03/10 07:50:55 by gdel-giu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ECHO = echo
ENV = env
PWD = pwd
FILES = *.c

OBJS = *.o

all :
	@gcc echo.c -o $(ECHO)
	@#bash ../piggy
	@#bash ../piggy0
	@#@afplay -v 0.5 '??.mp3'
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