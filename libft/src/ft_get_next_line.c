/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:27:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/09 11:37:08 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_stj_gnl(char *s1, char *s2, size_t len)
{
	char	*join;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = len;
	join = malloc((len1 + len2 + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, len1 + 1);
	ft_strlcpy(join + len1, s2, len2 + 1);
	free(s1);
	return (join);
}

static int	ft_reset(char **line, char **newline, size_t *to_count)
{
	if (*newline != NULL)
	{
		*to_count = *newline - *line + 1;
		return (1);
	}
	else
	{
		*to_count = ft_strlen(*line);
		return (0);
	}
}

char	*gnl(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*newline;
	char		*line;
	size_t		to_count;
	size_t		bytes_reads;

	line = ft_strdup(buf);
	bytes_reads = read(fd, buf, BUFFER_SIZE);
	while (!(ft_strchr(line, '\n') && bytes_reads > 0))
	{
		buf[bytes_reads] = '\0';
		line = ft_stj_gnl(line, buf, bytes_reads);
		bytes_reads = read(fd, buf, BUFFER_SIZE);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	newline = ft_strchr(line, '\n');
	if (ft_reset(&line, &newline, &to_count))
		ft_strlcpy(buf, newline + 1, BUFFER_SIZE + 1);
	else
		ft_strlcpy(buf, "", BUFFER_SIZE + 1);
	return (line[to_count] = '\0', line);
}
