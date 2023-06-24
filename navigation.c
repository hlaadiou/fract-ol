/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:20:32 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/24 15:21:27 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	restore_window(t_data *data)
{
	data->coord = (t_coord){MX_I, MX_F, MY_I, MY_F};
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

void	zoom_in(int mouse_x, int mouse_y, t_data *data)
{
	t_cmplx	focus_pt;
	t_var	vars;

	focus_pt = map_coord(mouse_x, mouse_y, data->coord);
	vars.x_interval = (data->coord.x_f - data->coord.x_i) / ZOOM_FACTOR;
	vars.y_interval = (data->coord.y_f - data->coord.y_i) / ZOOM_FACTOR;
	if (vars.x_interval > EPSILON  && vars.y_interval > EPSILON)
	{
		data->coord.x_i = focus_pt.re - (vars.x_interval / 2.0);
		data->coord.x_f = focus_pt.re + (vars.x_interval / 2.0);
		data->coord.y_i = focus_pt.im - (vars.y_interval / 2.0);
		data->coord.y_f = focus_pt.im + (vars.y_interval / 2.0);
	}
	printf("%lf %lf\n", vars.x_interval, vars.y_interval);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
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
	printf("%lf %lf\n", vars.x_interval, vars.y_interval);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

void	move_left(t_data *data)
{
	double	x_unit;

	x_unit = (data->coord.x_f - data->coord.x_i) / WIN_W;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	(data->coord.x_i) -= 10 * x_unit;
	(data->coord.x_f) -= 10 * x_unit;
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

void	move_right(t_data *data)
{
	double	x_unit;

	x_unit = (data->coord.x_f - data->coord.x_i) / WIN_W;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	(data->coord.x_i) += 10 * x_unit;
	(data->coord.x_f) += 10 * x_unit;
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

void	move_up(t_data *data)
{
	double	y_unit;

	y_unit = (data->coord.y_f - data->coord.y_i) / WIN_H;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	(data->coord.y_i) -= 10 * y_unit;
	(data->coord.y_f) -= 10 * y_unit;
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

void	move_down(t_data *data)
{
	double	y_unit;

	y_unit = (data->coord.y_f - data->coord.y_i) / WIN_H;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	(data->coord.y_i) += 10 * y_unit;
	(data->coord.y_f) += 10 * y_unit;
	render_mandelbrot(&data->img, data->coord);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}
