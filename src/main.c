/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:54 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/06 17:31:49 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))
#define SGN(_x) ((_x) < 0 ? -1 : ((_x) > 0 ? 1 : 0))

void	draw_horizontal_line(t_state state, t_point start, t_point dest)
{
	int	incr;

	incr = SGN(dest.projected_x - start.projected_x);
	while (start.projected_x != dest.projected_x)
	{
		image_put_pixel(&state.img, start.projected_x, start.projected_y,
			0xFFFFFF);
		start.projected_x += incr;
	}
}

void	draw_vertical_line(t_state state, t_point start, t_point dest)
{
	int	incr;

	incr = SGN(dest.projected_y - start.projected_y);
	while (start.projected_y != dest.projected_y)
	{
		image_put_pixel(&state.img, start.projected_x, start.projected_y,
			0xFFFFFF);
		start.projected_y += incr;
	}
}

void	draw_horinzontaly_line(t_state state, t_point start, t_point dest)
{
	int	dx;
	int	dy;
	int	error;

	dx = dest.projected_x - start.projected_x;
	dy = dest.projected_y - start.projected_y;
	error = -ABS(dx);
	while (start.projected_x != dest.projected_x)
	{
		image_put_pixel(&state.img, start.projected_x, start.projected_y,
			0xFFFFFF);
		error += 2 * ABS(dy);
		if (error >= 0)
		{
			start.projected_y += SGN(dy);
			error += -2 * ABS(dx);
		}
		start.projected_x += SGN(dx);
	}
}

void	draw_verticaly_line(t_state state, t_point start, t_point dest)
{
	int	dx;
	int	dy;
	int	error;

	dx = dest.projected_x - start.projected_x;
	dy = dest.projected_y - start.projected_y;
	error = -ABS(dy);
	while (start.projected_y != dest.projected_y)
	{
		image_put_pixel(&state.img, start.projected_x, start.projected_y,
			0xFFFFFF);
		error += 2 * ABS(dx);
		if (error >= 0)
		{
			start.projected_x += SGN(dx);
			error += -2 * ABS(dy);
		}
		start.projected_y += SGN(dy);
	}
}

void	draw_line(t_state state, t_point start, t_point dest)
{
	int	dx;
	int	dy;

	dx = dest.projected_x - start.projected_x;
	dy = dest.projected_y - start.projected_y;
	if (dy == 0)
		draw_horizontal_line(state, start, dest);
	else if (dx == 0)
		draw_vertical_line(state, start, dest);
	else if (ABS(dx) >= ABS(dy))
		draw_horinzontaly_line(state, start, dest);
	else
		draw_verticaly_line(state, start, dest);
}

void	compute_and_draw(t_state state)
{
	double	measure;
	int		x;
	int		y;

	measure = 4.0 * (double)WINDOW_HEIGHT / 5.0 / (double)state.map.height;
	measure = 100;
	y = 0;
	while (y < state.map.height)
	{
		x = 0;
		while (x < state.map.width)
		{
			// state.map.map[y][x].projected_y = (int)(y * measure
			// 		+ (double)WINDOW_HEIGHT / 10.0);
			// state.map.map[y][x].projected_x = (int)(x * measure
			// 		+ (double)WINDOW_WIDTH / 10.0);
			// state.map.map[x][y].projected_x = (int)((double)(x
			// 			- state.map.map[x][y].z) * cos(DEG_30) * measure
			// 		+ (double)WINDOW_HEIGHT / 10.0);
			state.map.map[y][x].projected_x = (int)((x - state.map.map[y][x].z)
					* cos(DEG_30) * measure + (double)WINDOW_WIDTH / 10.0);
			state.map.map[y][x].projected_y = (int)((y + (x
							+ state.map.map[y][x].z) * sin(DEG_30)) * measure
					+ (double)WINDOW_HEIGHT / 10.0);
			// state.map.map[y][x].projected_x = (int)((x - y) * cos(0.8)
			// *measure
			// 		+ (double)WINDOW_WIDTH / 10.0);
			// state.map.map[y][x].projected_y = (int)(((y + x) * sin(0.8)
			// 			* measure - state.map.map[y][x].z)
			// 		+ (double)WINDOW_HEIGHT / 10.0);
			if (x > 0)
				draw_line(state, state.map.map[y][x], state.map.map[y][x - 1]);
			if (y > 0)
				draw_line(state, state.map.map[y][x], state.map.map[y - 1][x]);
			x++;
		}
		y++;
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
