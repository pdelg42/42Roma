# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 09:29:45 by gdel-giu          #+#    #+#              #
#    Updated: 2023/03/27 10:38:20 by gdel-giu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft.a
LISTFT = liblistft.a

DIR1 = ../srcs/libft
DIR2 = ../srcs/listft
SRCS = *.c
FSRCS1 = ${wildcard $(DIR1)/$(SRCS)}
FSRCS2 = $(DIR2)/$(SRCS)

OBJS1 = $(FSRCS1:.c=.o)
OBJS2 = $(FSRCS2:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

all: $(LIBFT) $(LISTFT)

$(LIBFT): $(OBJS1)
	ar rcs $(LIBFT) $(OBJS1)

$(LISTFT): $(OBJS2)
	ar rcs $(LISTFT) $(OBJS2)

$(DIR1)/%.o: $(DIR1)/%.c
	$(CC) -c $(CFLAGS) $< -o $@
	
$(DIR2)/%.o: $(DIR2)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS1)
	rm -f $(OBJS2)

fclean:
	rm -f $(OBJS1)
	rm -f $(OBJS2)
	rm -f $(LIBFT)
	rm -f $(LISTFT)

re: fclean $(LIBFT) $(LISTFT)

.PHONY: all clean fclean re
