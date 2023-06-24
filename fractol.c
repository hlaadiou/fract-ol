/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:10:04 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/24 20:45:07 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*pixel;
	
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == SCROLL_UP)
		zoom_in(x, y, data);
	else if (button == SCROLL_DOWN)
		zoom_out(x, y, data);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESCAPE)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == ARROW_LEFT)
		move_left(data);
	else if (keycode == ARROW_RIGHT)
		move_right(data);
	else if (keycode == ARROW_UP)
		move_up(data);
	else if (keycode == ARROW_DOWN)
		move_down(data);
	else if (keycode == H_KEY)
		restore_window(data);
	return (0);
}

int	render(t_data *data, char **args)
{
	if (data->win_ptr == NULL)
		return (1);
	data->coord = (t_coord){MX_I, MX_F, MY_I, MY_F};
	data->cst = (t_cmplx){ft_atod(args[1]), ft_atod(args[2])};
	render_juliaset(&data->img, data->coord, data->cst);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_tolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	skip_spaces(char *str, int *i, int *j)
{
	while (str[*i] && (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13)))
	{
		(*i)++;
		(*j)++;
	}
	return ;
}

int	ft_valid_double(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	skip_spaces(str, &i, &j);
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
	{
		i++;
		j++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '.' && i != j && str[i + 1])
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	skip_spaces(str, &i, &j);
	if (i == ft_strlen(str) && i != j)
		return (1);
	return (0);
}

int	check_arguments(int ac, char **args)
{
	if (ac == 2)
	{
		if (!ft_strcmp(ft_tolower(args[1]), "mandelbrot"))
			return (1);
		else if (!ft_strcmp(ft_tolower(args[1]), "burningship"))
			return (3);
	}
	else if (ac == 4)
	{
		if (!ft_strcmp(ft_tolower(args[1]), "julia") && ft_valid_double(args[2]) \
			&& ft_valid_double(args[3]))
			return (2);
	}
	else
		print_options();
	return (-1);
}

int main(int ac, char **av)
{
	t_data	data;
	
	(void)ac;
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
	render(&data, &av[1]);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
}
