/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:06:22 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/16 18:38:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/* Window */
# define WIN_W 750
# define WIN_H 750
/* Algo */
# define MAX_ITER 25
/* Colors */
# define RED   0xFF0000
# define GREEN 0xFF00
# define BLUE  0xFF
# define PURPLE 0x9F2B68
# define APRICOT 0xF3C065
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define CREAM 0xF6E8B1
# define DARK_VANILLA 0xD4CAA3
# define IVORY 0xFFFEF2
/* KeyCodes */
# define ESCAPE 53
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_UP 126
# define ARROW_DOWN 125
/* Coordinates */
# define X_I -2.0
# define X_F 1.0
# define Y_I -1.5
# define Y_F 1.5
/* Includes */
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_coord
{
	double	x_i;
	double	x_f;
	double	y_i;
	double	y_f;
}	t_coord;

typedef struct s_img
{
    void    *mlx_img;
    char    *addr;
    int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
	t_img	img;
	t_coord	coord;
}   t_data;

typedef struct s_cmplx
{
	double	re;
	double	im;
}	t_cmplx;

#endif