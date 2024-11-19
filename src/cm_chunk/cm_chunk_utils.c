// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_chunk_utils.c                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/09/27 01:42:35 by rgramati          #+#    #+#             //
//   Updated: 2024/11/19 18:02:55 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CM_CHUNK_IMPLEMENTATION
# define CM_CHUNK_IMPLEMENTATION
#endif
#include <cmem.h>

void	*cm_chunk_at(t_cm_chunk *chunk_ptr, uint32_t index)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	while (index >= chunk->size && cm_chunk_next(chunk))
	{
		index -= chunk->size;
		chunk = cm_chunk_next(chunk);
	}
	if (index >= chunk->size)
		return (NULL);
	return (&chunk->data[index * chunk->alignment]);
}

uint32_t	cm_chunk_index(t_cm_chunk *chunk_ptr, void *elem)
{
	struct s_cm_chunk	*chunk;
	uint32_t			index;
	uint32_t			offset;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	index = 0;
	if (elem)
	{
		offset = (uintptr_t)elem - (uintptr_t)chunk;
		while (offset > sizeof(struct s_cm_chunk))
		{
			chunk = cm_chunk_next(chunk);
			if (!chunk)
				return ((uint32_t)-1);
			offset = (uintptr_t)elem - (uintptr_t)chunk;
		}
		index = (uintptr_t)elem - (uintptr_t)&chunk->data;
		if (index & (chunk->alignment - 1))
			index = ((uint32_t)-1);
		else
			index >>= CM_BIT_COUNT[chunk->alignment];
	}
	return (index);
}
