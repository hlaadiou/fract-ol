/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 05:37:13 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/26 15:57:30 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Takes the coordinates of a mapped pixel and decides if it is in the M set.
int	mandelbrot(t_cmplx c)
{
	int		iterations;
	t_cmplx	z;

	z = c;
	iterations = 0;
	while (iterations < MAX_ITER && squared_modulus(z) <= 4.0)
	{
		z = complex_sum(complex_square(z), c);
		iterations++;
	}
	return (iterations);
}

void	render_mandelbrot(t_img *img, t_coord coord)
{
	t_var	m_vars;
	int		iterations;
	int		x;
	int		y;

	m_vars.x_unit = (coord.x_f - coord.x_i) / WIN_W;
	m_vars.y_unit = (coord.y_f - coord.y_i) / WIN_H;
	m_vars.j = coord.y_i;
	y = 0;
	while (m_vars.j < coord.y_f)
	{
		x = 0;
		m_vars.i = coord.x_i;
		while (m_vars.i < coord.x_f)
		{
			iterations = mandelbrot((t_cmplx){m_vars.i, m_vars.j});
			put_pixel_img(img, x++, y, iterations * (255 / MAX_ITER));
			m_vars.i += m_vars.x_unit;
		}
		m_vars.j += m_vars.y_unit;
		y++;
	}
}
