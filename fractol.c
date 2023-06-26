/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:10:04 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/26 15:40:26 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void leak()
{
	system("leaks fractol");
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*pixel;
	
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

void	render_fractal(t_data *data)
{
	if (data->fractal == MANDELBROT)
		render_mandelbrot(&data->img, data->coord);
	else if (data->fractal == JULIA)
		render_juliaset(&data->img, data->coord, data->cst);
	else if (data->fractal == BURNINGSHIP)
		render_burningship(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

int main(int ac, char **av)
{
	t_data	data;
	
	atexit(leak);
	data.fractal = check_arguments(&data, ac, av);
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
	render_fractal(&data);
	mlx_hook(data.win_ptr, DESTROY_NOTIFY, 0, quit, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
}
