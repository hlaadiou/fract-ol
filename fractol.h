/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:06:22 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/11 11:46:09 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/* Window */
# define WIN_W 800
# define WIN_H 600
/* Colors */
# define RED   0xFF0000
# define GREEN 0xFF00
# define BLUE  0xFF
# define PURPLE 0x9F2B68
# define YELLOW 0xFFBF00
# define WHITE 0xFFFFFF
/* Algo */
# define MAX_ITER 42

/* Coordinates */
# define X_I -2.25
# define X_F 1
# define Y_I -1
# define Y_F 1

#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_rect
{
    int x;
    int y;
    int width;
    int height;
    int color;   
}   t_rect;

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
}   t_data;

typedef struct s_coord
{
    double  a;
    double  b;
    int     x;
    int     y;
}   t_coord;

#endif