// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_access.c                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/09/27 01:42:35 by rgramati          #+#    #+#             //
//   Updated: 2024/11/05 19:40:28 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef CM_CHUNK_IMPLEMENTATION
# define CM_CHUNK_IMPLEMENTATION
#endif
#include <cmem.h>

void	*cm_chunk_at(t_cm_chunk *chunk_ptr, uint32_t index)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	while (index >= chunk->size && chunk->next)
	{
		index -= chunk->size;
		chunk = chunk->next;
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
			if (!chunk->next)
				return ((uint32_t)-1);
			chunk = chunk->next;
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

void	*cm_chunk_it_start(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	return (chunk->iterator.start);
}

void	*cm_chunk_it_end(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	return (chunk->iterator.end);
}

void	*cm_chunk_it_next(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	if (chunk->iterator.it == NULL)
		chunk->iterator.it = &chunk->data;
	else
	{
		chunk->iterator.it += chunk->alignment;
		chunk->iterator.index++;
		if (chunk->iterator.it > chunk->iterator.end || \
			chunk->iterator.index >= chunk->size)
		{
			chunk->iterator.it = NULL;
			chunk->iterator.index = 0;
		}
	}
	return (chunk->iterator.it);
}
