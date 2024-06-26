/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 14:59:50 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/01 14:21:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// z = z2 + c

double	init_julia(t_fractol *data, double iter, double x, double y)
{
	double	var;

	iter = 0;
	while ((x * x) + (y * y) < 4 && iter < MAX_ITER)
	{
		var = x;
		x = (x * x) - (y * y) + data->julia[X];
		y = 2 * y * var + data->julia[Y];
		iter++;
	}
	return (iter);
}

void	julia(t_fractol *data)
{
	double	iter;
	int		colour;
	double	x;
	double	y;
	double	pos[2];

	x = 0;
	y = 0;
	while (x < data->win_width)
	{
		pos[X] = data->x[LT] + (x / data->win_width) * (data->x[RT] - data->x[LT]);
		while (y < data->win_height)
		{
			pos[Y] = data->y[UP] + (y / data->win_height) * (data->y[DN] - data->y[UP]);
			iter = init_julia(data, data->iter, pos[X], pos[Y]);
			if (iter == MAX_ITER)
				colour = 0xFF;
			else
				colour = get_rgba(data, iter);
			mlx_put_pixel(data->img, x, y, colour);
			y++;
		}
		x++;
		y = 0;
	}
}

int	julia_args(t_fractol *data, char **argv)
{
	data->julia[0] = ft_atof(argv[2]);
	data->julia[1] = ft_atof(argv[3]);
	if (data->julia[1] > 2 || data->julia[1] < -2)
		return (ft_help(), EXIT_FAILURE);
	if (data->julia[0] > 2 || data->julia[0] < -2)
		return (ft_help(), EXIT_FAILURE);
	return (0);
}
