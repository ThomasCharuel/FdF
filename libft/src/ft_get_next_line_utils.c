/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:40:51 by tcharuel          #+#    #+#             */
/*   Updated: 2023/12/04 11:37:13 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the length of a string.
 * Length includes the the terminating \n character,
 * except if the string does not include a \n character.
 * In this case, the regular length of the string is returned.
 *
 * @param s: The string to get the length from;
 *
 * @return Length until first Line Feed (included)
 */
size_t	ft_strlen_delimiter(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		if (s[len++] == c)
			return (len);
	}
	return (len);
}

/**
 * @brief Duplicates a string up to the first line feed ('\n') character.
 *
 * This function creates a duplicate of the string 'src', copying characters
 * up to (included) the first occurrence of the line feed character.
 * The duplication process stops either at the first line feed character
 * or at the end of the string if no line feed is found.
 *
 * @param src The source string to be duplicated.
 *
 * @return A pointer to the duplicated string, which is null-terminated.
 * @retval NULL if the string length is 0 or the allocation fails.
 */
char	*ft_strdup_lf(const char *src)
{
	size_t	len;
	char	*dup;

	len = ft_strlen_delimiter(src, '\n');
	if (!len)
		return (NULL);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	dup[len] = '\0';
	while (len-- > 0)
		dup[len] = src[len];
	return (dup);
}

/**
 * @brief Checks if the input string contains a LINE FEED character.
 *
 * This function scans the input string 's' to check if it contains
 * the character \n. It returns 1 if found within 's',
 * and 0 otherwise.
 *
 * @param s The input string to be searched.
 *
 * @return 1 if \n (LINE FEED) is found in the string 's', otherwise 0.
 */
int	ft_str_has_lf(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Copies the string pointed to by src to the buffer pointed to by dst.
 *

	* @param dst Pointer to the destination array where the content is to be copied.
 * @param src Pointer to the source string to be copied.
 */
void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
