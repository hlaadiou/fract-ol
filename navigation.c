/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:20:32 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/23 20:21:36 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	restore_window(t_data *data)
{
	data->max_iter = MAX_ITER;
	if (data->fractal == MANDELBROT)
		data->coord = (t_coord){MX_I, MX_F, MY_I, MY_F};
	else if (data->fractal == JULIA)
		data->coord = (t_coord){JX_I, JX_F, JY_I, JY_F};
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr \
	(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	render_fractal(data);
}

int	change_precision(t_data *data, int keycode)
{
	if (keycode == PAGE_UP && data->max_iter < MAX_ITER * 10)
		data->max_iter += 5;
	else if (keycode == PAGE_DOWN && data->max_iter >= MAX_ITER + 5)
		data->max_iter -= 5;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr \
	(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	render_fractal(data);
	return (0);
}

void	zoom_in(int mouse_x, int mouse_y, t_data *data)
{
	t_cmplx	focus_pt;
	t_var	vars;

	focus_pt = map_coord(mouse_x, mouse_y, data->coord);
	vars.x_interval = (data->coord.x_f - data->coord.x_i) / ZOOM_FACTOR;
	vars.y_interval = (data->coord.y_f - data->coord.y_i) / ZOOM_FACTOR;
	if (vars.x_interval > EPSILON && vars.y_interval > EPSILON)
	{
		data->coord.x_i = focus_pt.re - (vars.x_interval / 2.0);
		data->coord.x_f = focus_pt.re + (vars.x_interval / 2.0);
		data->coord.y_i = focus_pt.im - (vars.y_interval / 2.0);
		data->coord.y_f = focus_pt.im + (vars.y_interval / 2.0);
	}
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr \
	(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	render_fractal(data);
}

void	zoom_out(int mouse_x, int mouse_y, t_data *data)
{
	t_cmplx	focus_pt;
	t_var	vars;

	focus_pt = map_coord(mouse_x, mouse_y, data->coord);
	vars.x_interval = (data->coord.x_f - data->coord.x_i) * ZOOM_FACTOR;
	vars.y_interval = (data->coord.y_f - data->coord.y_i) * ZOOM_FACTOR;
	data->coord.x_i = focus_pt.re - (vars.x_interval / 2.0);
	data->coord.x_f = focus_pt.re + (vars.x_interval / 2.0);
	data->coord.y_i = focus_pt.im - (vars.y_interval / 2.0);
	data->coord.y_f = focus_pt.im + (vars.y_interval / 2.0);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr \
	(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	render_fractal(data);
}

int	change_color(t_data *data, int keycode)
{
	if (keycode == N_KEY)
		data->color_factor = -1;
	else if (keycode == ENTER \
	&& data->color_factor <= 1000 && data->color_factor > 0)
		data->color_factor = 2 * data->color_factor;
	else
		data->color_factor = 53;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr \
	(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	render_fractal(data);
	return (0);
}
