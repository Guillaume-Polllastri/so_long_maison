/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:24:01 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/14 17:44:26 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *) s;
	while (n > 0)
	{
		*ptr = '\0';
		ptr++;
		n--;
	}
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*read_buffer(char **buffer)
{
	char	*stock;
	char	*res;
	int		len;

	if (!*buffer || !ft_strchr(*buffer, '\n'))
		return (NULL);
	len = ft_strchr(*buffer, '\n') - *buffer;
	res = ft_substr(*buffer, 0, len + 1);
	stock = *buffer;
	*buffer = ft_substr(*buffer, len + 1, ft_strlen(*buffer) - (len + 1));
	free(stock);
	return (res);
}

static ssize_t	write_buffer(int fd, char **buffer)
{
	char	*tmp;
	char	*stock;
	ssize_t	status;

	tmp = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(*tmp));
	status = read(fd, tmp, BUFFER_SIZE);
	if (!*buffer && status > 0)
		*buffer = tmp;
	else if (status > 0)
	{
		stock = *buffer;
		*buffer = ft_strjoin(*buffer, tmp);
		free(stock);
		free(tmp);
	}
	else
		free(tmp);
	return (status);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	ssize_t		status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = 1;
	while (status > 0)
	{
		line = read_buffer(&buffer);
		if (line)
			return (line);
		status = write_buffer(fd, &buffer);
		if (status < 0)
			return (free(buffer), buffer = NULL, NULL);
		if (status == 0)
		{
			if (buffer == NULL || ft_strlen(buffer) == 0)
				return (free(buffer), buffer = NULL, NULL);
			line = ft_substr(buffer, 0, ft_strlen(buffer));
			return (free(buffer), buffer = NULL, line);
		}
	}
	return (NULL);
}
