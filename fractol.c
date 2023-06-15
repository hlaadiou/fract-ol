/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:10:04 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/15 21:23:57 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	modulus(t_cmplx c)
{
	return (sqrt(pow(c.re, 2) + pow(c.im, 2)));
}

t_cmplx	complex_square(t_cmplx z)
{
	t_cmplx	square;

	square.re = pow(z.re, 2) - pow(z.im, 2);
	square.im = 2 * z.re * z.im;
	return (square);
}

t_cmplx	complex_sum(t_cmplx x, t_cmplx y)
{
	t_cmplx	sum;

	sum.re = x.re + y.re;
	sum.im = x.im + y.im;
	return (sum);
}

// A function that maps the coordinates of the window in the complex plane.
t_cmplx	map_coord(int x, int y, t_coord coord)
{
	t_cmplx	c;

	c.re = coord.x_i + x * ((coord.x_f - coord.x_i) / WIN_W);
	c.im = coord.y_i + y * ((coord.y_f - coord.y_i) / WIN_H);
	return (c);
}

// Takes the coordinates of a mapped pixel and decides if it is in the M set.
int	mandelbrot(t_cmplx c)
{
	t_cmplx	z;
	int		iterations;

	z = c;
	iterations = 0;
	while (iterations < MAX_ITER && modulus(z) <= 2.0)
	{
		z = complex_sum(complex_square(z), c);
		iterations++;
	}
	return (iterations);
}

// int handle_keypress(int keysym, t_data *data)
// {
// 	if (keysym == XK_Escape)
// 	{
// 		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
// 	    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		data->win_ptr = NULL;
// 	}
// 	return (0);
// }

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESCAPE)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*pixel;
	
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			put_pixel_img(img, j++, i, color);
		}
		++i;
	}
	return ;
}

// Depending on the calculations plots a colored pixel in the window.
void	render_mandelbrot(t_img *img, t_coord coord)
{
	int	iterations;
	int	i;
	int	j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while(i < WIN_W)
		{
			iterations = mandelbrot(map_coord(i, j, coord));
			put_pixel_img(img, i, j, BLUE - (iterations * BLUE / MAX_ITER));
			// if (iterations == MAX_ITER)
			// 	put_pixel_img(img, i, j, WHITE);
			// else
			// 	put_pixel_img(img, i, j, WHITE * iterations * 8);
			i++;
		}
		j++;
	}
}

void	zoom_in(int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	(data->coord.x_i) += 0.2;
	(data->coord.x_f) -= 0.2;
	(data->coord.y_i) += 0.1;
	(data->coord.y_f) -= 0.1;
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

void	zoom_out(int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	(data->coord.x_i) -= 0.2;
	(data->coord.x_f) += 0.2;
	(data->coord.y_i) -= 0.1;
	(data->coord.y_f) += 0.1;
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == SCROLL_UP)
		zoom_in(x, y, data);
	else if (button == SCROLL_DOWN)
		zoom_out(x, y, data);
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	data->coord = (t_coord){X_I, X_F, Y_I, Y_F};
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int main(void)
{
	t_data	data;
	
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	    return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "Fract-ol");
	if (data.win_ptr == NULL)
	{
	    free(data.win_ptr);
	    return (1);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	//SETUP HOOKS
	render(&data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
}
