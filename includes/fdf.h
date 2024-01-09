/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:59:01 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 14:15:38 by tcharuel         ###   ########.fr       */
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

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define M_PI 3.14159265358979323846
# define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))
# define SGN(_x) ((_x) < 0 ? -1 : ((_x) > 0 ? 1 : 0))
# define MOUSE_LEFT_CLICK 1
# define MOUSE_RIGHT_CLICK 3
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5

# define ERROR -1
# define SUCCESS 0

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	double	init_x;
	double	init_y;
	double	init_z;
	double	proj_x;
	double	proj_y;
}			t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		bytes_per_pixel;
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
	int		prev_mouse_x;
	int		prev_mouse_y;
	double	measure;
	double	offset_x;
	double	offset_y;
	double	angle_rotate_z;
	double	angle_rotate_x;
	double	depth_factor;
	double	scale_factor;
}			t_state;

int			init_state(t_state *state);
void		setup_state_params(t_state *state);
int			cleanup_exit(t_state *state);

void		reset_image(t_state state);
void		image_put_pixel(t_data *data, int x, int y, int color);
void		compute_and_draw(t_state state);

int			cleanup_exit(t_state *state);

int			handle_mouse_press(int button, int x, int y, t_state *state);
int			handle_mouse_release(int button, int x, int y, t_state *state);
int			handle_mouse_move(int x, int y, t_state *state);
int			handle_key_hook(int keycode, t_state *state);

int			parse_map(char *file_path, t_map *map);

void		draw_line(t_state state, t_point start, t_point dest);

#endif