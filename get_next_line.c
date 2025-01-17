/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:29:37 by gmaccha-          #+#    #+#             */
/*   Updated: 2024/10/24 14:29:40 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*store_part(char *store)
{
	char	*new_store;
	char	*ptr;
	int		len;

	ptr = ft_strchr(store, '\n');
	if (!ptr)
	{
		new_store = NULL;
		return (ft_free(&store));
	}
	else
		len = (ptr - store) + 1;
	if (!store[len])
		return (ft_free(&store));
	new_store = ft_substr(store, len, ft_strlen(store)-len);
	ft_free(&store);
	if (!new_store)
		return (NULL);
	return (new_store);
}

char	*get_new_line(char *store)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(store, '\n');
	len = (ptr - store) + 1;
	line = ft_substr(store, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_part(int fd, char *store)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&store));
	buffer[0] = '\0';
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			store = ft_strjoin(store, buffer);
		}
	}
	free(buffer);
	if (bytes_read == -1)
		return (ft_free(&store));
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((store && !ft_strchr(store, '\n')) || !store)
		store = read_part(fd, store);
	if (!store)
		return (NULL);
	line = get_new_line(store);
	if (!line)
		return (ft_free(&store));
	store = store_part(store);
	return (line);
}
