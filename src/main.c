/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:54 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/04 18:24:16 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

int	close_window(int keycode, t_vars *vars)
{
	(void)keycode;
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;

	if (argc == 2)
	{
		(void)(argv);
		vars.mlx = mlx_init();
		if (!vars.mlx)
			return (1);
		vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
		if (!vars.win)
			return (1);
		img.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
		mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
		mlx_hook(vars.win, 2, 1L << 0, close_window, &vars);
		mlx_loop(vars.mlx);
	}
	return (0);
}
