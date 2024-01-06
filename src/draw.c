/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:03:46 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/06 22:56:48 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	image_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	reset_image(t_state state)
{
	ft_bzero(state.img.addr, WINDOW_HEIGHT * WINDOW_WIDTH
		* (state.img.bits_per_pixel / 8));
}

void	rotate_z(t_point *point, double angle)
{
	double	y;
	double	x;

	x = point->double_x;
	y = point->double_y;
	point->double_x = x * cos(angle) - y * sin(angle);
	point->double_y = x * sin(angle) + y * cos(angle);
}

void	rotate_x(t_point *point, double angle, double measure)
{
	point->double_y = point->double_y * cos(angle) - point->z * measure
		* sin(angle);
}

void	compute_and_draw(t_state state)
{
	double measure;
	int x;
	int y;
	int offset_x;
	int offset_y;

	reset_image(state);
	if (state.map.width > 1)
	{
		measure = 3.0 * (double)WINDOW_WIDTH / 5.0 / ((double)state.map.width
				- 1.0);
	}
	else
	{
		measure = 1;
	}
	offset_x = (WINDOW_WIDTH - state.map.width * measure * cos(M_PI / 2.5)) / 2;
	offset_y = WINDOW_HEIGHT / 3;
	y = 0;
	while (y < state.map.height)
	{
		x = 0;
		while (x < state.map.width)
		{
			state.map.map[y][x].double_x = x * measure;
			state.map.map[y][x].double_y = y * measure;
			rotate_z(&state.map.map[y][x], state.angle);
			rotate_x(&state.map.map[y][x], atan(sqrt(2)), measure);
			state.map.map[y][x].x = (int)state.map.map[y][x].double_x + offset_x
				+ state.translation_x;
			state.map.map[y][x].y = (int)state.map.map[y][x].double_y + offset_y
				+ state.translation_y;
			if (x > 0)
				draw_line(state, state.map.map[y][x], state.map.map[y][x - 1]);
			if (y > 0)
				draw_line(state, state.map.map[y][x], state.map.map[y - 1][x]);
			x++;
		}
		y++;
	}
	ft_printf("X: %d, y: %d\n", state.translation_x, state.translation_y);
	mlx_put_image_to_window(state.mlx, state.win, state.img.img, 0, 0);
}