/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:54 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/07 00:07:09 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc == 2)
	{
		if (init_state(&state) == ERROR || parse_map(argv[1],
				&(state.map)) == ERROR)
			cleanup_exit(&state);
		compute_and_draw(state);
		mlx_key_hook(state.win, handle_key_hook, &state);
		mlx_mouse_hook(state.win, handle_mouse_hook, &state);
		mlx_hook(state.win, DestroyNotify, NoEventMask, cleanup_exit, &state);
		mlx_loop(state.mlx);
	}
	return (0);
}
