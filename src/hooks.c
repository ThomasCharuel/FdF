/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:06:00 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/05 11:06:19 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	cleanup_exit(t_state *state)
{
	mlx_destroy_window(state->mlx, state->win);
	mlx_destroy_image(state->mlx, state->img.img);
	exit(0);
}

int	handle_key_hook(int keycode, t_state *state)
{
	if (keycode == XK_Escape)
	{
		cleanup_exit(state);
	}
	return (0);
}
