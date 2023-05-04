/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:07:10 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/05/04 12:09:30 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "window.h"

int	size = 10;
int	follow = 0;
int	color = 0;

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

int	exit_tutorial(t_win	*window)
{
	if (window)
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	exit(EXIT_SUCCESS);
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

int	get_color()
{
	return (rand() % 2147483647);
}

int	read_keys(int key_pressed, void *param)
{
	t_img	*img;

	img = (t_img *)param;
	if (key_pressed == ESC || !img)
		exit_tutorial(&img->win);
	else if (key_pressed == ENTER)
		draw_square((t_square){0, 0, img->w, 0xFFFFFF}, *img);
	else if (key_pressed == FOLLOW)
		follow = !follow;
	else if (key_pressed == COLOR)
		color = get_color();
	else
		return (-1);
	mlx_put_image_to_window(img->win.win_ptr, img->win.win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int read_mouse(int button, int mouse_x, int mouse_y, void *param)
{
	int 		x;
	int 		y;
	t_img 		*img;
	t_square	s;

	img = (t_img *) param;
	if (!img)
		return (-1);
	if (mouse_x < 0 || mouse_y < 0 || mouse_x > img->w || mouse_y > img->h)
		return (2);
	x = ((mouse_x % img->w) / size) * size;
	y = ((mouse_y % img->h) / size) * size;
	s = (t_square){x, y, size, color};
	draw_square(s, *img);
	mlx_put_image_to_window(img->win.mlx_ptr, img->win.win_ptr, img->img_ptr, 0, 0);
	(void)button;
	return (0);
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
		draw_square((t_square){0, 0, 300, 0xFFFFFF}, image);
		mlx_put_image_to_window(image.win.mlx_ptr, image.win.win_ptr, image.img_ptr, 0, 0);
	}
	/* KEY HOOK */
	mlx_key_hook(tutorial.win_ptr, read_keys, &image);
	/* MOUSE HOOK */
	mlx_mouse_hook(tutorial.win_ptr, read_mouse, &image);
	mlx_hook(tutorial.win_ptr, 17, 0, exit_tutorial, &tutorial);
	mlx_loop(tutorial.mlx_ptr);
	return (0);
}
