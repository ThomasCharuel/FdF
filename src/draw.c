/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:03:46 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 16:31:32 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	image_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT))
		return ;
	dst = data->addr + (y * data->line_length + x * data->bytes_per_pixel);
	*(unsigned int *)dst = color;
}

void	reset_image(t_state state)
{
	size_t	i;
	int		*image;

	image = (int *)state.img.addr;
	i = 0;
	while (i < WINDOW_HEIGHT * WINDOW_WIDTH)
	{
		if (image[i] != 0)
			image[i] = 0;
		i++;
	}
}

void	rotate_z(t_point *point, t_state state)
{
	point->proj_x = point->init_x * cos(state.angle_rotate_z) - point->init_y
		* sin(state.angle_rotate_z);
	point->proj_y = point->init_x * sin(state.angle_rotate_z) + point->init_y
		* cos(state.angle_rotate_z);
}

void	rotate_x(t_point *point, t_state state)
{
	point->proj_z = point->proj_y * sin(state.angle_rotate_x) + (point->init_z
			+ state.depth_factor * point->init_z) * cos(state.angle_rotate_x);
	point->proj_y = point->proj_y * cos(state.angle_rotate_x) - (point->init_z
			+ state.depth_factor * point->init_z) * sin(state.angle_rotate_x);
}

void	rotate_y(t_point *point, t_state state)
{
	point->proj_x = point->proj_x * cos(state.angle_rotate_y) + (point->proj_z)
		* sin(state.angle_rotate_y);
}

void	compute_and_draw(t_state state)
{
	int	x;
	int	y;

	reset_image(state);
	y = 0;
	while (y < state.map.height)
	{
		x = 0;
		while (x < state.map.width)
		{
			rotate_z(&state.map.map[y][x], state);
			rotate_x(&state.map.map[y][x], state);
			rotate_y(&state.map.map[y][x], state);
			state.map.map[y][x].x = (int)(state.map.map[y][x].proj_x
					* state.scale_factor + state.offset_x);
			state.map.map[y][x].y = (int)(state.map.map[y][x].proj_y
					* state.scale_factor + state.offset_y);
			if (x > 0)
				draw_line(state, state.map.map[y][x], state.map.map[y][x - 1]);
			if (y > 0)
				draw_line(state, state.map.map[y][x], state.map.map[y - 1][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(state.mlx, state.win, state.img.img, 0, 0);
	mlx_do_sync(state.mlx);
}
