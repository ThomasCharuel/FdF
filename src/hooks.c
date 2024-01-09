/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:06:00 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 14:03:03 by tcharuel         ###   ########.fr       */
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
	return (SUCCESS);
}

int	handle_mouse_press(int button, int x, int y, t_state *state)
{
	state->prev_mouse_x = x;
	state->prev_mouse_y = y;
	state->button_pressed = button;
	if (button == MOUSE_WHEEL_DOWN)
	{
		state->depth_factor += 1.0 / 8;
		compute_and_draw(*state);
	}
	else if (button == MOUSE_WHEEL_UP)
	{
		state->depth_factor -= 1.0 / 8;
		compute_and_draw(*state);
	}
	return (SUCCESS);
}

int	handle_mouse_release(int button, int x, int y, t_state *state)
{
	(void)x;
	(void)y;
	(void)button;
	state->button_pressed = 0;
	compute_and_draw(*state);
	return (SUCCESS);
}

int	handle_mouse_move(int x, int y, t_state *state)
{
	(void)state;
	if (state->button_pressed == MOUSE_LEFT_CLICK)
	{
		state->offset_x += (double)(x - state->prev_mouse_x);
		state->offset_y += (double)(y - state->prev_mouse_y);
		state->prev_mouse_x = x;
		state->prev_mouse_y = y;
	}
	return (SUCCESS);
}

int	handle_mouse_hook(int button, int x, int y, t_state *state)
{
	static int	prev_button = 0;
	static int	prev_x;
	static int	prev_y;

	if (button == MOUSE_LEFT_CLICK && prev_button == button)
	{
		state->offset_x += x - prev_x;
		state->offset_y += y - prev_y;
		compute_and_draw(*state);
	}
	else if (button == MOUSE_WHEEL_DOWN)
	{
		state->depth_factor += 1.0 / 8;
		compute_and_draw(*state);
	}
	else if (button == MOUSE_WHEEL_UP)
	{
		state->depth_factor -= 1.0 / 8;
		compute_and_draw(*state);
	}
	prev_button = button;
	prev_x = x;
	prev_y = y;
	return (SUCCESS);
}
