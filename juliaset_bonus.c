/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   juliaset_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:14:54 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/27 18:22:24 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	julia(t_cmplx z, t_data data)
{
	int		iterations;

	iterations = 0;
	while (iterations < data.max_iter && squared_modulus(z) <= 4.0)
	{
		z = complex_sum(complex_square(z), data.cst);
		iterations++;
	}
	return (iterations);
}

void	render_juliaset(t_data *data)
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
			iterations = julia((t_cmplx){m_vars.i, m_vars.j}, *data);
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
