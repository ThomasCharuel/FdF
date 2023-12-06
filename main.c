/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:54 by tcharuel          #+#    #+#             */
/*   Updated: 2023/12/06 14:04:30 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	void *mlx;                                                 // display
	void *mlx_win;                                             // window
	t_data image;                                              // image
	mlx = mlx_init();                                          // display init
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!"); // window init
	image.img = mlx_new_image(mlx, 1920, 1080);                // image init
}
