/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:25:14 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/06/24 05:34:31 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_skip_whites(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	return (i);
}

int	ft_check_sign(char *str, double *sign, int index)
{
	*sign = 1.0;
	if (str[index] == '-')
	{
		*sign *= -1.0;
		index++;
	}
	else if (str[index] == '+')
		index++;
	return (index);
}

double	ft_atod(char *str)
{
	t_double	nb;
	int			i;

	nb.whole = 0.0;
	nb.decimal = 1.0;
	i = ft_skip_whites(str);
	i = ft_check_sign(str, &nb.sign, i);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb.whole = nb.whole * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb.decimal /= 10;
		nb.whole += nb.decimal * (str[i] - '0');
		i++;
	}
	return (nb.whole * nb.sign);
}
