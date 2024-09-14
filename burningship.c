/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 05:38:48 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/27 17:42:23 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	burningship(t_cmplx c, t_data data)
{
	int		iterations;
	t_cmplx	z;

	z = c;
	iterations = 0;
	while (iterations < data.max_iter && squared_modulus(z) <= 4.0)
	{
		z.re = fabs(z.re);
		z.im = fabs(z.im);
		z = complex_sum(complex_square(z), c);
		iterations++;
	}
	return (iterations);
}

void	render_burningship(t_data *data)
{
	t_var	m_vars;
	int		iterations;
	int		x;
	int		y;

	m_vars.x_unit = (data->coord.x_f - data->coord.x_i) / WIN_W;
	m_vars.y_unit = (data->coord.y_f - data->coord.y_i) / WIN_H;
	m_vars.j = data->coord.y_i;
	y = 0;
	while (m_vars.j < data->coord.y_f)
	{
		x = 0;
		m_vars.i = data->coord.x_i;
		while (m_vars.i < data->coord.x_f)
		{
			iterations = burningship((t_cmplx){m_vars.i, m_vars.j}, *data);
			if (iterations == data->max_iter)
				put_pixel_img(&data->img, x++, y, BLACK);
			else
				put_pixel_img(&data->img, x++, y, calc_color(data, iterations));
			m_vars.i += m_vars.x_unit;
		}
		m_vars.j += m_vars.y_unit;
		y++;
	}
}
