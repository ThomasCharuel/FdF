/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:54 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/05 19:32:26 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_state state, t_point start, t_point dest)
{
	int	dx;
	int	dy;
	int	err;

	dx = dest.projected_x - start.projected_x;
	dy = dest.projected_y - start.projected_y;
	err = abs(dx) - abs(dy);
	while (start.projected_x != dest.projected_x
		|| start.projected_y != dest.projected_y)
	{
		image_put_pixel(&state.img, start.projected_x, start.projected_y,
			0xFFFFFF);
		if (2 * err >= dy)
		{
			err -= abs(dy);
			if (start.projected_x < dest.projected_x)
				start.projected_x += 1;
			else
				start.projected_x -= 1;
		}
		if (2 * err <= dx)
		{
			err += abs(dx);
			if (start.projected_y < dest.projected_y)
				start.projected_y += 1;
			else
				start.projected_y -= 1;
		}
	}
}

void	compute_and_draw(t_state state)
{
	double	measure;
	int		x;
	int		y;

	measure = 4.0 * (double)WINDOW_HEIGHT / 5.0 / (double)state.map.height;
	x = 0;
	while (x < state.map.height)
	{
		y = 0;
		while (y < state.map.width)
		{
			state.map.map[x][y].projected_x = (int)(x * measure
					+ (double)WINDOW_HEIGHT / 10.0);
			state.map.map[x][y].projected_y = (int)(y * measure
					+ (double)WINDOW_WIDTH / 10.0);
			if (x > 0)
				draw_line(state, state.map.map[x][y], state.map.map[x - 1][y]);
			if (y > 0)
				draw_line(state, state.map.map[x][y], state.map.map[x][y - 1]);
			y++;
		}
		x++;
	}
}

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc == 2)
	{
		if (init_state(&state) == ERROR || parse_map(argv[1],
				&(state.map)) == ERROR)
			cleanup_exit(&state);
		compute_and_draw(state);
		mlx_put_image_to_window(state.mlx, state.win, state.img.img, 0, 0);
		mlx_key_hook(state.win, handle_key_hook, &state);
		mlx_hook(state.win, DestroyNotify, NoEventMask, cleanup_exit, &state);
		mlx_loop(state.mlx);
	}
	return (0);
}

// t_point	get_projection(int x, int y, int z, int angle)
// {
// 	t_point	point;

// 	point.x = x * cos(angle) + y * cos(angle + 2) + z * cos(angle - 2);
// 	point.y = x * sin(angle) + y * sin(angle + 2) + z * sin(angle - 2);
// 	return (point);
// }
