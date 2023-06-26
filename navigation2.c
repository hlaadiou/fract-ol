/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:42:36 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/26 15:43:12 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_left(t_data *data)
{
	double	x_unit;

	x_unit = (data->coord.x_f - data->coord.x_i) / WIN_W;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	data->coord.x_i -= TR_UNIT * x_unit;
	data->coord.x_f -= TR_UNIT * x_unit;
	render_fractal(data);
}

void	move_right(t_data *data)
{
	double	x_unit;

	x_unit = (data->coord.x_f - data->coord.x_i) / WIN_W;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	(data->coord.x_i) += TR_UNIT * x_unit;
	(data->coord.x_f) += TR_UNIT * x_unit;
	render_fractal(data);
}

void	move_up(t_data *data)
{
	double	y_unit;

	y_unit = (data->coord.y_f - data->coord.y_i) / WIN_H;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	(data->coord.y_i) -= TR_UNIT * y_unit;
	(data->coord.y_f) -= TR_UNIT * y_unit;
	render_fractal(data);
}

void	move_down(t_data *data)
{
	double	y_unit;

	y_unit = (data->coord.y_f - data->coord.y_i) / WIN_H;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	(data->coord.y_i) += TR_UNIT * y_unit;
	(data->coord.y_f) += TR_UNIT * y_unit;
	render_fractal(data);
}
