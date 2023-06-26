# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 22:41:32 by hlaadiou          #+#    #+#              #
#    Updated: 2023/06/26 15:44:48 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= fractol.c math.c navigation.c mandelbrot.c juliaset.c \
			burningship.c ft_atod.c navigation2.c libft_utils.c events.c \
			input_validation.c
OBJS		= $(SRCS:.c=.o)
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -O3 -g
LFLAGS		= -lmlx -framework OpenGL -framework AppKit
RM			= rm -f
NAME		= fractol

%.o:		%.c fractol.h
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