/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:06:00 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/06 22:24:47 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_hook(int keycode, t_state *state)
{
	if (keycode == XK_Escape)
		cleanup_exit(state);
	return (SUCCESS);
}

int	handle_mouse_hook(int button, int x, int y, t_state *state)
{
	static int	prev_button = 0;
	static int	prev_x;
	static int	prev_y;

	ft_printf("Button: %d x:%d y:%d\n", button, x, y);
	if (prev_button == button)
	{
		if (button == MOUSE_LEFT_CLICK)
		{
			state->translation_x += x - prev_x;
			state->translation_y += y - prev_y;
			compute_and_draw(*state);
		}
	}
	prev_button = button;
	prev_x = x;
	prev_y = y;
	return (SUCCESS);
}
