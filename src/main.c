/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:54 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/05 11:06:30 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc == 2)
	{
		(void)(argv);
		state.mlx = mlx_init();
		if (!state.mlx)
			return (1);
		state.win = mlx_new_window(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
				"FdF");
		if (!state.win)
			return (1);
		state.img.img = mlx_new_image(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		state.img.addr = mlx_get_data_addr(state.img.img,
				&state.img.bits_per_pixel, &state.img.line_length,
				&state.img.endian);
		image_put_pixel(&state.img, 5, 5, 0x00FF0000);
		mlx_put_image_to_window(state.mlx, state.win, state.img.img, 0, 0);
		mlx_key_hook(state.win, handle_key_hook, &state);
		mlx_hook(state.win, DestroyNotify, NoEventMask, cleanup_exit, &state);
		mlx_loop(state.mlx);
	}
	return (0);
}
