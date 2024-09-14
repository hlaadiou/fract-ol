# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 22:41:32 by hlaadiou          #+#    #+#              #
#    Updated: 2023/06/27 20:23:17 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= fractol.c math.c navigation.c mandelbrot.c juliaset.c \
			burningship.c ft_atod.c navigation2.c libft_utils.c events.c \
			input_validation.c
SRCS_BONUS	= fractol_bonus.c math_bonus.c navigation_bonus.c mandelbrot_bonus.c juliaset_bonus.c \
			burningship_bonus.c ft_atod_bonus.c navigation2_bonus.c libft_utils_bonus.c events_bonus.c \
			input_validation_bonus.c
OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
LFLAGS		= -lmlx -framework OpenGL -framework AppKit
RM			= rm -f
NAME		= fractol
NAME_BONUS	= fractol_bonus

all:			$(NAME)

%_bonus.o:		%_bonus.c fractol_bonus.h
				$(CC) $(CFLAGS) -Imlx -O3 -c $< -o $@ 
			
%.o:			%.c fractol.h
				$(CC) $(CFLAGS) -Imlx -O3 -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

bonus:			$(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_BONUS)
				$(CC) $(OBJS_BONUS) $(LFLAGS) -o $(NAME_BONUS)
				
clean:
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean all

.PHONY:			all clean fclean bonus re