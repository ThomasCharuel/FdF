/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:02:27 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/06 22:07:18 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_state(t_state *state)
{
	state->mlx = NULL;
	state->win = NULL;
	state->map.map = NULL;
	state->map.width = 0;
	state->map.height = 0;
	state->angle = M_PI / 4;
	state->translation_x = 0;
	state->translation_y = 0;
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
