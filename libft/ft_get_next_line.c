/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:40:48 by tcharuel          #+#    #+#             */
/*   Updated: 2023/12/04 11:49:23 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns a line read from a
 * file descriptor.
 *
 * The returned line should include the terminating \n character,
 * except if the end of file was reached and does not end with a \n character.
 *
 * @param fd: The file descriptor to read from.
 *
 * @return Read line: correct behavior.
 * @retval NULL there is nothing else to read, or an error occurred
 */
char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	ssize_t		bytes_read;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		return (NULL);
	}
	bytes_read = read_in_stash(fd, &stash);
	if (bytes_read < 0)
	{
		if (stash)
			free(stash);
		stash = NULL;
		ft_putstr_fd("Error\n", STDERR_FILENO);
		return (NULL);
	}
	return (pick_line_in_stash(&stash));
}

/**
 * @brief Updates the stash by reading on file.
 *
 * This function takes the stash and add content from the file in it
 * until it finds a LINE FEED character or EOF.
 *
 * @param fd The file descriptor to read from.
 * @param stash The address of the stash string.
 *
 * @return The number of bytes read in the last read call.sss
 * @retval -2 if the allocation fails.
 */
ssize_t	read_in_stash(int fd, char **stash)
{
	ssize_t	bytes_read;
	char	*new_stash;
	size_t	stash_len;

	bytes_read = BUFFER_SIZE;
	while (bytes_read == BUFFER_SIZE && (!*stash || (*stash
				&& !ft_str_has_lf(*stash))))
	{
		if (*stash)
			stash_len = ft_strlen_delimiter(*stash, '\0');
		else
			stash_len = 0;
		new_stash = (char *)malloc((stash_len + BUFFER_SIZE + 1)
				* sizeof(char));
		if (!new_stash)
			return (-2);
		if (stash_len)
			ft_strcpy(new_stash, *stash);
		bytes_read = read(fd, &(new_stash[stash_len]), BUFFER_SIZE);
		new_stash[stash_len + bytes_read] = '\0';
		if (*stash)
			free(*stash);
		*stash = new_stash;
	}
	return (bytes_read);
}

/**
 * @brief Allocates and returns a string from the input stash.
 *
 * This function allocates memory for and returns a new substring from the
 * input string 'stash'. The substring starts from the beginning of the stash
 * and ends on the first \n character or \0 terminator.
 * The obtained string is removed from the stash.
 *
 * @param stash The address of the stash string.
 *
 * @return The newly allocated substring.
 * @retval NULL if the allocation fails.
 */
char	*pick_line_in_stash(char **stash)
{
	char	*line;
	char	*new_stash;

	line = ft_strdup_lf(*stash);
	if (!line || !ft_str_has_lf(line))
	{
		free(*stash);
		*stash = NULL;
	}
	else
	{
		new_stash = ft_substr(*stash, ft_strlen_delimiter(line, '\n'), -1);
		free(*stash);
		*stash = new_stash;
		if (!*stash)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
