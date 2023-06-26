/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:39:46 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/26 15:56:19 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_options(void)
{
	ft_putstr("╔═════════════════════════════════════════════════════════╗");
	ft_putstr("║                      FRACT-OL OPTIONS                   ║");
	ft_putstr("╠═════════════════════════════════════════════════════════╣");
	ft_putstr("║                                                         ║");
	ft_putstr("║  Welcome to FRACT-OL! Choose one of the options below:  ║");
	ft_putstr("║                                                         ║");
	ft_putstr("║ 1. Render the Mandelbrot set:                           ║");
	ft_putstr("║      ./fractol mandelbrot                               ║");
	ft_putstr("║                                                         ║");
	ft_putstr("║ 2. Render the Julia set:                                ║");
	ft_putstr("║      ./julia real_part imaginary_part                   ║");
	ft_putstr("║                                                         ║");
	ft_putstr("║ 3. Render the Burning Ship fractal:                     ║");
	ft_putstr("║      ./fractol burningship                              ║");
	ft_putstr("║                                                         ║");
	ft_putstr("╚═════════════════════════════════════════════════════════╝");
	exit(EXIT_FAILURE);
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
	if (str[i] == '.' && str[i + 1] && str[i + 1] != ' ' && i != j)
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	skip_spaces(str, &i, &j);
	if (i == ft_strlen(str) && i != j)
		return (1);
	return (0);
}

int	check_arguments(t_data *data, int ac, char **args)
{
	if (ac == 2)
	{
		if (!ft_strcmp(ft_tolower(args[1]), "mandelbrot"))
		{
			data->coord = (t_coord){MX_I, MX_F, MY_I, MY_F};
			return (1);
		}
		else if (!ft_strcmp(ft_tolower(args[1]), "burningship"))
		{
			data->coord = (t_coord){BSX_I, BSX_F, BSY_I, BSY_F};
			return (3);
		}
	}
	else if (ac == 4)
	{
		if (!ft_strcmp(ft_tolower(args[1]), "julia") && \
			ft_valid_double(args[2]) && ft_valid_double(args[3]))
		{
			data->coord = (t_coord){JX_I, JX_F, JY_I, JY_F};
			data->cst = (t_cmplx){ft_atod(args[2]), ft_atod(args[3])};
			return (2);
		}
	}
	print_options();
	return (-1);
}
