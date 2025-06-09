/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:51:11 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/09 15:06:59 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
