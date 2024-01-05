/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:47:25 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/05 15:30:48 by tcharuel         ###   ########.fr       */
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
		if (line[i] != ' ' && !ft_isdigit(line[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	*line_to_int_list(char *line, int length)
{
	char	**elements;
	int		*res;
	int		i;

	elements = ft_split(line, ' ');
	if (!elements)
		return (NULL);
	res = (int *)malloc(length * sizeof(int));
	if (!res)
	{
		ft_free_strs(elements);
		return (NULL);
	}
	i = 0;
	while (elements[i])
	{
		res[i] = ft_atoi(elements[i]);
		i++;
	}
	ft_free_strs(elements);
	return (res);
}

int	add_line_to_map(t_map *map, char *line)
{
	int	**new_map;

	if (check_line(line) == ERROR || compute_width(line) != map->width)
		return (ERROR);
	map->height++;
	new_map = (int **)malloc(map->height * sizeof(int *));
	if (!new_map)
		return (ERROR);
	if (map->height > 1)
	{
		ft_memcpy(new_map, map->map, (map->height - 1) * sizeof(int *));
		free(map->map);
	}
	map->map = new_map;
	map->map[map->height - 1] = line_to_int_list(line, map->width);
	if (!map->map[map->height - 1])
		return (ERROR);
	return (SUCCESS);
}

int	parse_map(char *file_path, t_map *map)
{
	int		fd;
	char	*line;

	(void)map;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(strerror(errno));
		return (ERROR);
	}
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("Empty file.");
		close(fd);
		return (ERROR);
	}
	map->width = compute_width(line);
	while (line)
	{
		if (add_line_to_map(map, line) == ERROR)
		{
			free(line);
			ft_printf("Memory error.");
			close(fd);
			return (ERROR);
		}
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);
}
