/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:01:47 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 17:02:08 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	image_put_pixel(&state.img, start.x, start.y, 0xFFFFFF);
	if (dy == 0)
		draw_horizontal_line(state, start, dest);
	else if (dx == 0)
		draw_vertical_line(state, start, dest);
	else if (ABS(dx) >= ABS(dy))
		draw_horinzontaly_line(state, start, dest);
	else
		draw_verticaly_line(state, start, dest);
}
