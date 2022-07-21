/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:14:49 by mcamargo          #+#    #+#             */
/*   Updated: 2022/06/10 10:29:13 by mcamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *store, int fd)
{
	int		i;
	char	buffer[BUFFER_SIZE + 1];
	char	*line;

	i = read (fd, &buffer, BUFFER_SIZE);
	while (i > 0)
	{
		buffer[i] = '\0';
		line = store;
		store = ft_strjoin(store, buffer);
		free(line);
		if (ft_strchr(store, '\n') != -1)
		{
			break ;
		}
		i = read (fd, &buffer, BUFFER_SIZE);
	}
	return (store);
}

char	*ft_checkline(char	**store)
{
	char			*newstr;
	char			*auxstr;
	unsigned int	i;

	if (*store == NULL)
		return (NULL);
	i = 0;
	auxstr = NULL;
	while ((*store)[i] && (*store)[i] != '\n')
		i++;
	if ((*store)[i] == '\n')
		newstr = ft_substr(*store, 0, i + 1);
	else
		newstr = ft_substr(*store, 0, i);
	if (ft_strlen(*store) - i > 0 && ft_strlen(*store) - i - 1 > 0)
		auxstr = ft_substr(*store, i + 1, ft_strlen(*store) - i - 1);
	free(*store);
	*store = auxstr;
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX)
		return (NULL);
	if (ft_strchr(store, '\n'))
		store = get_line(store, fd);
	line = ft_checkline(&store);
	return (line);
}
