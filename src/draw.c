/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:03:46 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/06 17:02:53 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	image_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// void	draw_line(t_state state, t_point start, t_point dest)
// {
// 	int	dx;
// 	int	dy;
// 	int	err;

// 	dx = dest.projected_x - start.projected_x;
// 	dy = dest.projected_y - start.projected_y;
// 	err = abs(dx) - abs(dy);
// 	while (start.projected_x != dest.projected_x
// 		|| start.projected_y != dest.projected_y)
// 	{
// 		if (start.projected_x > 0 && start.projected_x < WINDOW_HEIGHT
// 			&& start.projected_y > 0 && start.projected_y < WINDOW_WIDTH)
// 			image_put_pixel(&state.img, start.projected_x, start.projected_y,
// 				0xFFFFFF);
// 		(void)state;
// 		if (2 * err >= dy)
// 		{
// 			err -= abs(dy);
// 			if (start.projected_x < dest.projected_x)
// 				start.projected_x += 1;
// 			else
// 				start.projected_x -= 1;
// 		}
// 		if (2 * err <= dx)
// 		{
// 			err += abs(dx);
// 			if (start.projected_y < dest.projected_y)
// 				start.projected_y += 1;
// 			else
// 				start.projected_y -= 1;
// 		}
// 	}
// }
