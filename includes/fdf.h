/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:59:01 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/05 11:45:22 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/includes/libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_state
{
	void	*mlx;
	void	*win;
	t_data	img;
}			t_state;

void		image_put_pixel(t_data *data, int x, int y, int color);

int			create_trgb(int t, int r, int g, int b);

int			cleanup_exit(t_state *state);
int			handle_key_hook(int keycode, t_state *state);

#endif