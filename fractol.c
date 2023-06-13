/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:10:04 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/13 21:53:17 by hlaadiou         ###   ########.fr       */
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
t_cmplx	map_coord(int x, int y)
{
	t_cmplx	c;

	c.re = X_I + x * ((X_F - X_I) / WIN_W);
	c.im = Y_I + y * ((Y_F - Y_I) / WIN_H);
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
void	render_mandelbrot(t_img *img)
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
			iterations = mandelbrot(map_coord(i, j));
			put_pixel_img(img, i, j, WHITE - (iterations * WHITE / MAX_ITER));
			// if (iterations == MAX_ITER)
			// 	put_pixel_img(img, i, j, WHITE);
			// else
			// 	put_pixel_img(img, i, j, WHITE * iterations * 8);
			i++;
		}
		j++;
	}
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
 	render_background(&data->img, IVORY);
	render_mandelbrot(&data->img);
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
	// mlx_loop_hook(data.mlx_ptr, &render, &data);
	// mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	render(&data);
	mlx_loop(data.mlx_ptr);
	// mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
