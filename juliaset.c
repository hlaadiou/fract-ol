/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   juliaset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 05:38:11 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/26 15:57:05 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_cmplx z, t_cmplx c)
{
	int		iterations;

	iterations = 0;
	while (iterations < MAX_ITER && squared_modulus(z) <= 4.0)
	{
		z = complex_sum(complex_square(z), c);
		iterations++;
	}
	return (iterations);
}

void	render_juliaset(t_img *img, t_coord coord, t_cmplx cst)
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
			iterations = julia((t_cmplx){m_vars.i, m_vars.j}, cst);
			put_pixel_img(img, x++, y, iterations * (255 / MAX_ITER));
			m_vars.i += m_vars.x_unit;
		}
		m_vars.j += m_vars.y_unit;
		y++;
	}
}
