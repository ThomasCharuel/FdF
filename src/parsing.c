/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:47:25 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 18:15:47 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	compute_width(char *line)
{
	int	is_word;
	int	count;
	int	i;

	is_word = 0;
	count = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && !ft_isdigit(line[i]) && line[i] != '-')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

t_point	*line_to_point_list(char *line, int length)
{
	char	**elements;
	t_point	*res;
	int		i;

	elements = ft_split(line, ' ');
	if (!elements)
		return (NULL);
	res = (t_point *)malloc(length * sizeof(t_point));
	if (!res)
	{
		ft_free_strs(elements);
		return (NULL);
	}
	i = 0;
	while (elements[i])
	{
		res[i].z = ft_atoi(elements[i]);
		i++;
	}
	ft_free_strs(elements);
	return (res);
}

int	add_line_to_map(t_map *map, char *line)
{
	t_point	**new_map;

	if (check_line(line) == ERROR || compute_width(line) != map->width)
		return (ERROR);
	map->height++;
	new_map = (t_point **)malloc(map->height * sizeof(t_point *));
	if (!new_map)
		return (ERROR);
	if (map->height > 1)
	{
		ft_memcpy(new_map, map->map, (map->height - 1) * sizeof(t_point *));
		free(map->map);
	}
	map->map = new_map;
	map->map[map->height - 1] = line_to_point_list(line, map->width);
	if (!map->map[map->height - 1])
		return (ERROR);
	return (SUCCESS);
}

int	parse_map(char *file_path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open_file(file_path);
	if (fd == ERROR)
		return (ERROR);
	line = get_first_line(fd, map);
	if (!line)
		return (ERROR);
	while (line)
	{
		if (add_line_to_map(map, line) == ERROR)
		{
			ft_printf("Memory error.");
			close(fd);
			free(line);
			return (ERROR);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);
}
