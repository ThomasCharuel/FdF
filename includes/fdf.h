/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:59:01 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/06 20:05:19 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/includes/libft.h"
# include "/home/tcharuel/Desktop/minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

// # define WINDOW_WIDTH 1920
// # define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 400
# define WINDOW_HEIGHT 500
# define M_PI 3.14159265358979323846
# define DEG_30 (M_PI / 6.0)

# define ERROR -1
# define SUCCESS 0

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	double	double_x;
	double	double_y;
}			t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_map
{
	t_point	**map;
	int		width;
	int		height;
}			t_map;

typedef struct s_state
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	map;
	double	angle;
}			t_state;

int			init_state(t_state *state);
int			cleanup_exit(t_state *state);

int			create_trgb(int t, int r, int g, int b);
void		image_put_pixel(t_data *data, int x, int y, int color);

int			cleanup_exit(t_state *state);
int			handle_key_hook(int keycode, t_state *state);

int			parse_map(char *file_path, t_map *map);

#endif