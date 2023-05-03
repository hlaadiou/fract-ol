/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:07:10 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/05/04 00:10:31 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "window.h"

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *)dst = color;
	}
	return ;
}

void	draw_square(t_square square, t_img img)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < square.size && i + square.y < img.h)
	{
		j = 0;
		while (j < square.size && j + square.x < img.w)
		{
			put_pixel_img(img, j + square.x, i + square.y, square.color);
			j++;
		}
		i++;
	}
}

int	exit_tutorial(t_win	*window)
{
	if (window)
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	exit(EXIT_SUCCESS);
}

int	main(void)
{
	t_win	tutorial;
	t_img	image;

	tutorial = new_program(300, 300, "tutorial");
	if (!tutorial.win_ptr)
		return (2);
	image = new_image(300, 300, tutorial);

	{
		/* Draw a giant pixel */
		draw_square((t_square){0, 0, 300, 0x000000FF}, image);
		mlx_put_image_to_window(image.win.mlx_ptr, image.win.win_ptr, image.img_ptr, 0, 0);
	}
	mlx_hook(tutorial.win_ptr, 17, 0, exit_tutorial, &tutorial);
	mlx_loop(tutorial.mlx_ptr);
	return (0);
}
