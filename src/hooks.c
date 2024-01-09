/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:06:00 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 14:24:36 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_hook(int keycode, t_state *state)
{
	if (keycode == XK_Escape)
		cleanup_exit(state);
	if (keycode == XK_KP_Add)
		state->scale_factor /= 0.9;
	else if (keycode == XK_KP_Subtract)
		state->scale_factor *= 0.9;
	else if (keycode == XK_Left)
		state->angle_rotate_z += M_PI / 16;
	else if (keycode == XK_Right)
		state->angle_rotate_z -= M_PI / 16;
	else if (keycode == XK_Up)
		state->angle_rotate_x += M_PI / 16;
	else if (keycode == XK_Down)
		state->angle_rotate_x -= M_PI / 16;
	compute_and_draw(*state);
	return (SUCCESS);
}

int	handle_mouse_press(int button, int x, int y, t_state *state)
{
	state->prev_mouse_x = x;
	state->prev_mouse_y = y;
	if (button == MOUSE_WHEEL_DOWN)
	{
		state->depth_factor += 0.2;
		compute_and_draw(*state);
	}
	else if (button == MOUSE_WHEEL_UP)
	{
		state->depth_factor -= 0.2;
		compute_and_draw(*state);
	}
	return (SUCCESS);
}

int	handle_mouse_release(int button, int x, int y, t_state *state)
{
	if (button == MOUSE_LEFT_CLICK)
	{
		state->offset_x += (double)(x - state->prev_mouse_x);
		state->offset_y += (double)(y - state->prev_mouse_y);
		compute_and_draw(*state);
	}
	return (SUCCESS);
}
