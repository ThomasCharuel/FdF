/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:54 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/06 21:59:32 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))
#define SGN(_x) ((_x) < 0 ? -1 : ((_x) > 0 ? 1 : 0))

void	draw_horizontal_line(t_state state, t_point start, t_point dest)
{
	int	incr;

	incr = SGN(dest.x - start.x);
	while (start.x != dest.x)
	{
		image_put_pixel(&state.img, start.x, start.y, 0xFFFFFF);
		start.x += incr;
	}
}

void	draw_vertical_line(t_state state, t_point start, t_point dest)
{
	int	incr;

	incr = SGN(dest.y - start.y);
	while (start.y != dest.y)
	{
		image_put_pixel(&state.img, start.x, start.y, 0xFFFFFF);
		start.y += incr;
	}
}

void	draw_horinzontaly_line(t_state state, t_point start, t_point dest)
{
	int	dx;
	int	dy;
	int	error;

	dx = dest.x - start.x;
	dy = dest.y - start.y;
	error = -ABS(dx);
	while (start.x != dest.x)
	{
		image_put_pixel(&state.img, start.x, start.y, 0xFFFFFF);
		error += 2 * ABS(dy);
		if (error >= 0)
		{
			start.y += SGN(dy);
			error += -2 * ABS(dx);
		}
		start.x += SGN(dx);
	}
}

void	draw_verticaly_line(t_state state, t_point start, t_point dest)
{
	int	dx;
	int	dy;
	int	error;

	dx = dest.x - start.x;
	dy = dest.y - start.y;
	error = -ABS(dy);
	while (start.y != dest.y)
	{
		image_put_pixel(&state.img, start.x, start.y, 0xFFFFFF);
		error += 2 * ABS(dx);
		if (error >= 0)
		{
			start.x += SGN(dx);
			error += -2 * ABS(dy);
		}
		start.y += SGN(dy);
	}
}

void	draw_line(t_state state, t_point start, t_point dest)
{
	int	dx;
	int	dy;

	dx = dest.x - start.x;
	dy = dest.y - start.y;
	if (dy == 0)
		draw_horizontal_line(state, start, dest);
	else if (dx == 0)
		draw_vertical_line(state, start, dest);
	else if (ABS(dx) >= ABS(dy))
		draw_horinzontaly_line(state, start, dest);
	else
		draw_verticaly_line(state, start, dest);
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

void	rotate_x(t_point *point, double angle)
{
	point->double_y = point->double_y * cos(angle) - point->z * sin(angle);
}

void	compute_and_draw(t_state state)
{
	double	measure;
	int		x;
	int		y;
	int		offset_x;
	int		offset_y;

	// Il faut que le premier point soit a WINDOW_WIDTH / 10
	// Il faut que le dernier point soit a WINDOW_WIDTH / 10 * 9
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
			state.map.map[y][x].z *= measure;
			rotate_z(&state.map.map[y][x], state.angle);
			rotate_x(&state.map.map[y][x], atan(sqrt(2)));
			state.map.map[y][x].x = (int)state.map.map[y][x].double_x
				+ offset_x;
			state.map.map[y][x].y = (int)state.map.map[y][x].double_y
				+ offset_y;
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
