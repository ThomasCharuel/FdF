/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:06:00 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/07 00:03:33 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_hook(int keycode, t_state *state)
{
	if (keycode == XK_Escape)
		cleanup_exit(state);
	if (keycode == 65451)
	{
		state->scale_factor /= 0.9;
		compute_and_draw(*state);
	}
	if (keycode == 65453)
	{
		state->scale_factor *= 0.9;
		compute_and_draw(*state);
	}
	printf("Scale: %f\n", state->scale_factor);
	return (SUCCESS);
}

int	handle_mouse_hook(int button, int x, int y, t_state *state)
{
	static int	prev_button = 0;
	static int	prev_x;
	static int	prev_y;

	if (button == MOUSE_LEFT_CLICK && prev_button == button)
	{
		state->translation_x += x - prev_x;
		state->translation_y += y - prev_y;
		compute_and_draw(*state);
	}
	else if (button == MOUSE_WHEEL_DOWN)
	{
		state->depth_factor += 1;
		compute_and_draw(*state);
	}
	else if (button == MOUSE_WHEEL_UP)
	{
		state->depth_factor -= 1;
		compute_and_draw(*state);
	}
	prev_button = button;
	prev_x = x;
	prev_y = y;
	return (SUCCESS);
}
