/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:02:27 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 17:53:43 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setup_state_params(t_state *state)
{
	double	measure;
	int		x;
	int		y;

	state->angle_rotate_z = M_PI / 4;
	state->angle_rotate_x = atan(sqrt(2));
	state->angle_rotate_y = 0;
	state->scale_factor = 1;
	state->depth_factor = 0;
	if (state->map.width > 1)
		measure = 3.0 * (double)WINDOW_WIDTH / 5.0 / ((double)state->map.width
				- 1.0);
	else if (state->map.height > 1)
		measure = 3.0 * (double)WINDOW_HEIGHT / 5.0 / ((double)state->map.height
				- 1.0);
	else
		measure = 1;
	state->offset_x = (WINDOW_WIDTH - (state->map.width - 1) * measure
			* cos(0.6109)) / 2;
	state->offset_y = WINDOW_HEIGHT / 3;
	y = 0;
	while (y < state->map.height)
	{
		x = 0;
		while (x < state->map.width)
		{
			state->map.map[y][x].init_x = x * measure;
			state->map.map[y][x].init_y = y * measure;
			state->map.map[y][x].init_z = state->map.map[y][x].z * measure;
			x++;
		}
		y++;
	}
}

int	init_state(t_state *state)
{
	state->mlx = NULL;
	state->win = NULL;
	state->map.map = NULL;
	state->map.width = 0;
	state->map.height = 0;
	state->mlx = mlx_init();
	if (!state->mlx)
		return (ERROR);
	state->win = mlx_new_window(state->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (!state->win)
		return (ERROR);
	state->img.img = mlx_new_image(state->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!state->img.img)
		return (ERROR);
	state->img.addr = mlx_get_data_addr(state->img.img,
			&state->img.bits_per_pixel, &state->img.line_length,
			&state->img.endian);
	state->img.bytes_per_pixel = state->img.bits_per_pixel / 8;
	return (SUCCESS);
}

void	cleanup_map(t_map map)
{
	int	i;

	i = 0;
	while (i < map.height)
	{
		free(map.map[i]);
		i++;
	}
	free(map.map);
}

void	cleanup_state(t_state *state)
{
	if (state->win)
		mlx_destroy_window(state->mlx, state->win);
	if (state->img.img)
		mlx_destroy_image(state->mlx, state->img.img);
	if (state->map.map)
		cleanup_map(state->map);
	if (state->mlx)
	{
		mlx_destroy_display(state->mlx);
		free(state->mlx);
	}
}

int	cleanup_exit(t_state *state)
{
	cleanup_state(state);
	exit(SUCCESS);
}
