/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:54 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/05 18:35:13 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	compute_and_draw(t_state state)
{
	double	measure;
	int		x;
	int		y;
	int		a;
	int		b;

	measure = 4.0 * (double)WINDOW_HEIGHT / 5.0 / (double)state.map.height;
	x = 0;
	while (x < state.map.height)
	{
		y = 0;
		while (y < state.map.width)
		{
			a = (int)(x * measure + (double)WINDOW_HEIGHT / 10.0);
			b = (int)(y * measure + (double)WINDOW_WIDTH / 10.0);
			image_put_pixel(&state.img, b, a, 0xFFFFFF);
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
