/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   burningship.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/11 22:27:20 by smclacke      #+#    #+#                 */
/*   Updated: 2023/03/11 22:27:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// z = abs(z)2 + c

float	init_burning(float iter, float x1, float y1)
{
	float	var;
	float	x;
	float	y;

	x = x1;
	y = y1;
	iter = 0;
	while ((x * x) + (y * y) < 4 && iter < MAX_ITER)
	{
		var = x * x - y * y + x1;
		y = fabs(2 * x * y) - y1;
		x = var;
		iter++;
	}
	return (iter);
}

void	burningship(t_fractol *data)
{
	float	iter;
	int		colour;
	float	x;
	float	y;
	float	pos[2];

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		pos[X] = data->x[LT] + (x / WIDTH) * (data->x[RT] - data->x[LT]);
		while (y < HEIGHT)
		{
			pos[Y] = data->y[UP] + (y / HEIGHT) * (data->y[DN] - data->y[UP]);
			iter = init_burning(data->iter, pos[X], pos[Y]);
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