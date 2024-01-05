/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:06:00 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/05 13:41:06 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_hook(int keycode, t_state *state)
{
	if (keycode == XK_Escape)
		cleanup_exit(state);
	return (SUCCESS);
}
