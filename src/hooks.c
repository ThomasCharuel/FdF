/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:06:00 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 17:47:33 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_angles(t_state *state, double z, double x, double y)
{
	state->angle_rotate_z = z;
	state->angle_rotate_x = x;
	state->angle_rotate_y = y;
}

void	handle_angle_key(int keycode, t_state *state)
{
	if (keycode == XK_w)
		change_angles(state, 0, 0, 0);
	else if (keycode == XK_x)
		change_angles(state, 0, M_PI, 0);
	else if (keycode == XK_a)
		change_angles(state, 0, M_PI / 2, -M_PI / 2);
	else if (keycode == XK_s)
		change_angles(state, 0, M_PI / 2, 0);
	else if (keycode == XK_d)
		change_angles(state, 0, M_PI / 2, M_PI);
	else if (keycode == XK_f)
		change_angles(state, 0, M_PI / 2, M_PI / 2);
}

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
	handle_angle_key(keycode, state);
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
