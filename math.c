/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:24:07 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/26 15:57:54 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	squared_modulus(t_cmplx c)
{
	return ((c.re * c.re) + (c.im * c.im));
}

t_cmplx	complex_square(t_cmplx z)
{
	t_cmplx	square;

	square.re = (z.re * z.re) - (z.im * z.im);
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
