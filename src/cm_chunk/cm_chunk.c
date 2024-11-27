/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_chunk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:44:58 by rgramati          #+#    #+#             */
/*   Updated: 2024/09/23 20:23:11 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#ifndef CM_CHUNK_IMPLEMENTATION
# define CM_CHUNK_IMPLEMENTATION
#endif
#include <cmem.h>

t_cm_chunk	*cm_chunk_init(uint32_t elem_size, void *ptr, uint64_t link)
{
	struct s_cm_chunk	*chunk;
	uint32_t			offset;

	chunk = ptr;
	if (!ptr || !elem_size)
		chunk = malloc(sizeof(struct s_cm_chunk));
	if (chunk)
	{
		cm_memset(chunk, 0, sizeof(struct s_cm_chunk));
		offset = cm_pow2next(elem_size);
		chunk->capacity = CM_CHUNK_DATA_CAP / offset;
		chunk->alignment = offset;
		chunk->elem_size = elem_size;
		if (link)
			chunk->link = link - 1;
		if (!chunk->alignment || !chunk->capacity || offset < 8 || link > CM_CHUNK_LINK_MAX)
		{
			if (!ptr)
				free(chunk);
			chunk = NULL;
		}
	}
	return (chunk);
}

void	cm_chunk_clear(t_cm_chunk *chunk_ptr, uint32_t flags)
{
	struct s_cm_chunk	*chunk;
	t_cm_chunk			*tmp;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	tmp = cm_chunk_next(chunk);
	if (tmp == chunk + 1)
		cm_chunk_clear(tmp, flags);
	else if (tmp)
		cm_chunk_clear(tmp, flags & ~CM_CLEAR_STATIC);
	if (!chunk)
		return ;
	if (flags & CM_CLEAR_NULL)
		cm_memset(chunk, 0, 32);
	if ((flags & CM_CLEAR_FREE) == CM_CLEAR_FREE)
	{
		if (!(flags & CM_CLEAR_STATIC))
			free(chunk);
	}
}

void	*cm_chunk_alloc(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;
	struct s_cm_chunk	*tmp;
	void				*ptr;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	tmp = chunk;
	ptr = NULL;
	if (chunk)
	{
		ptr = chunk->free_list;
		if (ptr)
			chunk->free_list = chunk->free_list->next;
		while (tmp)
		{
			chunk = tmp;
			tmp = cm_chunk_next(chunk);
		}
		if (chunk->size >= chunk->capacity)
			chunk = cm_chunk_link(chunk);
		if (!ptr)
			ptr = &chunk->data[chunk->size * chunk->alignment];
		chunk->size++;
	}
	return (ptr);
}

void	*cm_chunk_push(t_cm_chunk *chunk_ptr, void *elem, uint32_t elem_size)
{
	struct s_cm_chunk	*chunk;
	void				*ptr;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	ptr = NULL;
	if (chunk && elem)
	{
		if (elem_size != chunk->elem_size)
			return (ptr);
		ptr = cm_chunk_alloc(chunk);
		if (ptr)
			cm_memcpy(ptr, elem, elem_size);
	}
	return (ptr);
}

void	cm_chunk_pop(t_cm_chunk *chunk_ptr, uint32_t index)
{
	struct s_cm_chunk	*chunk;
	void				*elem;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	if (chunk)
	{
		elem = cm_chunk_at(chunk, index);
		if (!elem)
			return ;
		((struct s_flist *)elem)->next = chunk->free_list;
		chunk->free_list = elem;
		while (chunk && index > chunk->capacity)
		{
			index -= chunk->capacity;
			chunk = cm_chunk_next(chunk);
		}
		chunk->size--;
	}
}
