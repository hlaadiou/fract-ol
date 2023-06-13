# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 22:41:32 by hlaadiou          #+#    #+#              #
#    Updated: 2023/06/12 17:59:19 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= fractol.c
OBJS		= $(SRCS:.c=.o)
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
LFLAGS		= -lmlx -framework OpenGL -framework AppKit
RM			= rm -f
NAME		= fractol

%.o:		%.c
			$(CC) $(CFLAGS) -Imlx -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re