/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:51:11 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/25 09:39:53 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	*ft_realloc(void *ptr, size_t old_elm, size_t new_elm, size_t size_elm)
{
	void	*new_ptr;

	new_ptr = malloc(size_elm * new_elm);
	if (ptr && new_ptr)
	{
		ft_memcpy(new_ptr, ptr, old_elm * size_elm);
		free(ptr);
	}
	return (new_ptr);
}

int	check_file_extend(char *filename)
{
	char	*str;

	str = ft_strchr(filename, '.');
	if (!str)
	{
		ft_printf("Error\nWrong name file\n");
		return (1);
	}
	if (ft_strncmp(str, ".ber", 5))
	{
		ft_printf("Error\nWrong name file\n");
		return (1);
	}
	return (0);
}

size_t	ft_strlen_no_nl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
