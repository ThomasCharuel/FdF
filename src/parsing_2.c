/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:47:25 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 18:14:40 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(strerror(errno));
		return (ERROR);
	}
	return (fd);
}

char	*get_first_line(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("Empty file.");
		close(fd);
		return (NULL);
	}
	map->width = compute_width(line);
	return (line);
}
