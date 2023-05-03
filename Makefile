# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 18:27:40 by hlaadiou          #+#    #+#              #
#    Updated: 2023/05/03 20:09:03 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= mlx_test.c window.c
OBJS		= $(SRCS:.c=.o)
CC			= cc
RM			= rm -f
NAME		= mlx_test

%.o:		%.c
			$(CC) -Wall -Werror -Wextra -Imlx -c $< -o $@

all:		$(NAME) clean

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re