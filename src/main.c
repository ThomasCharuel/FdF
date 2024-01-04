/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:54 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/04 17:32:22 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	void	*mlx;
	void	*win;

	// Initialiser la connexion avec le système graphique
	mlx = mlx_init();
	// Vérifier si l'initialisation a réussi
	if (!mlx)
		return (1);

	// Créer une nouvelle fenêtre graphique
	win = mlx_new_window(mlx, 800, 600, "Ma fenetre MiniLibX");
	// Vérifier si la création de la fenêtre a réussi
	if (!win)
		return (1);

	// Lancer la boucle d'événements pour traiter les entrées utilisateur
	mlx_loop(mlx);
	return (0);
}
