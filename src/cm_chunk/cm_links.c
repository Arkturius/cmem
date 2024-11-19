// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_links.c                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/08 18:03:50 by rgramati          #+#    #+#             //
//   Updated: 2024/11/19 18:38:33 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CM_CHUNK_IMPLEMENTATION
# define CM_CHUNK_IMPLEMENTATION
#endif
#include <cmem.h>

t_cm_chunk	*cm_chunk_next(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;

	chunk = chunk_ptr;
	if ((uint64_t)chunk->next > CM_CHUNK_LINK_MAX)
		return (chunk->next);
	return (NULL);
}

t_cm_chunk	*cm_chunk_link(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;
	void				*ptr;

	chunk = chunk_ptr;
	ptr = NULL;
	if (chunk->link > 0)
		ptr = ((uint8_t *)chunk) + sizeof(struct s_cm_chunk);
	chunk->next = cm_chunk_init(chunk->alignment, ptr, chunk->link);
	return (chunk->next);
}

uint32_t	cm_chunk_size(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;
	uint32_t			size;

	chunk = chunk_ptr;
	size = 0;
	while (chunk)
	{
		size += chunk->size;
		chunk = cm_chunk_next(chunk);
	}
	return (size);
}
