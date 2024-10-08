/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:14:09 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/27 20:28:39 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

/* Window */
# define WIN_W        800
# define WIN_H        750

/* Fractals */
# define MANDELBROT   1
# define JULIA        2
# define BURNINGSHIP  3

/* Algo */
# define MAX_ITER     100
# define TR_UNIT      15
# define ZOOM_FACTOR  1.5
# define EPSILON      0.00000000001

/* Colors */
# define RED          0xFF0000
# define GREEN        0xFF00
# define BLUE         0xFF
# define WHITE        0xFFFFFF
# define BLACK        0x000000

/* KeyCodes */
# define ESCAPE         53
# define SCROLL_UP      4
# define SCROLL_DOWN    5
# define MIDDLE_CLICK   3
# define ARROW_LEFT     123
# define ARROW_RIGHT    124
# define ARROW_UP       126
# define ARROW_DOWN     125
# define DESTROY_NOTIFY 17
# define PAGE_UP        116
# define PAGE_DOWN      121
# define ENTER          36
# define N_KEY          45

/* Coordinates */
// MANDELBROT
# define MX_I         -2.0
# define MX_F         1.0
# define MY_I         -1.5
# define MY_F         1.5
// JULIA
# define JX_I         -1.6
# define JX_F         1.6
# define JY_I         -1.2
# define JY_F         1.2
// TheBurningShip
# define BSX_I         -1.818606
# define BSX_F         -1.701551
# define BSY_I         -0.090231
# define BSY_F         0.026824

/* Includes */
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

/* Typedefs */
typedef struct s_coord
{
	double	x_i;
	double	x_f;
	double	y_i;
	double	y_f;
}	t_coord;

typedef struct s_img
{
	char	*addr;
	int		bpp;
	void	*mlx_img;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_cmplx
{
	double	re;
	double	im;
}	t_cmplx;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		fractal;
	int		max_iter;
	int		color_factor;
	t_img	img;
	t_coord	coord;
	t_cmplx	cst;
}	t_data;

typedef struct s_var
{
	double	x_interval;
	double	y_interval;
	double	x_unit;
	double	y_unit;
	double	i;
	double	j;
}	t_var;

typedef struct s_double
{
	double	whole;
	double	decimal;
	double	sign;
}	t_double;

/* Functions prototypes */
t_cmplx		complex_square(t_cmplx z);
t_cmplx		complex_sum(t_cmplx x, t_cmplx y);
t_cmplx		map_coord(int x, int y, t_coord coord);
double		ft_atod(char *str);
double		squared_modulus(t_cmplx c);
void		put_pixel_img(t_img *img, int x, int y, int color);
void		restore_window(t_data *data);
void		zoom_in(int mouse_x, int mouse_y, t_data *data);
void		zoom_out(int mouse_x, int mouse_y, t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);
void		move_up(t_data *data);
void		move_down(t_data *data);
int			mouse_hook(int button, int x, int y, t_data *data);
int			key_hook(int keycode, t_data *data);
int			quit(t_data *data);
void		render_fractal(t_data *data);
int			mandelbrot(t_cmplx c, t_data data);
void		render_mandelbrot(t_data *data);
int			julia(t_cmplx z, t_data data);
void		render_juliaset(t_data *data);
void		print_options(void);
void		skip_spaces(char *str, int *i, int *j);
int			ft_valid_double(char *str);
int			check_arguments(t_data *data, int ac, char **args);
int			burningship(t_cmplx c, t_data data);
void		render_burningship(t_data *data);
void		ft_putstr(char *s);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_tolower(char *str);
int			ft_strlen(char *str);
int			change_precision(t_data *data, int keycode);
int			calc_color(t_data *data, int iter);
int			change_color(t_data *data, int keycode);

#endif