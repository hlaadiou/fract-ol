/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:10:04 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/11 13:31:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// A function that maps the coordinates of the window in the complex plane.
void	map_coord(t_coord *coord)
{
	coord->a = X_I + coord->x * ((X_F - X_I) / WIN_W);
	coord->b = Y_I + coord->y * ((Y_F - Y_I) / WIN_H);
}

int	mandelbrot(t_coord coord)
{
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*pixel;
	
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	render_rectangle(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			put_pixel_img(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			put_pixel_img(img, j++, i, color);
		}
		++i;
	}
	return ;
}

void	render_mandelbrot(t_img *img)
{
	t_coord	coordinates;
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
 	render_background(&data->img, WHITE);
	put_pixel_img(&data->img, 100, 1, RED);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int main(void)
{
	t_data	data;
	
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	    return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "Fract-ol");
	if (data.win_ptr == NULL)
	{
	    free(data.win_ptr);
	    return (1);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	//SETUP HOOKS
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	
	mlx_loop(data.mlx_ptr);
		
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
