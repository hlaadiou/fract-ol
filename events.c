/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:38:17 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/26 15:38:42 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	quit(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(EXIT_SUCCESS);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == SCROLL_UP)
		zoom_in(x, y, data);
	else if (button == SCROLL_DOWN)
		zoom_out(x, y, data);
	else if (button == MIDDLE_CLICK)
		restore_window(data);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESCAPE)
		quit(data);
	else if (keycode == ARROW_LEFT)
		move_left(data);
	else if (keycode == ARROW_RIGHT)
		move_right(data);
	else if (keycode == ARROW_UP)
		move_up(data);
	else if (keycode == ARROW_DOWN)
		move_down(data);
	return (0);
}
