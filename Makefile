# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 22:41:32 by hlaadiou          #+#    #+#              #
#    Updated: 2023/05/14 01:45:27 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= fractol.c
OBJS		= $(SRCS:.c=.o)
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm -f
NAME		= fractol

%.o:		%.c
			$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re