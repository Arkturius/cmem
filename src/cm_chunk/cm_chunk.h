// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_chunk.h                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/06 00:36:49 by rgramati          #+#    #+#             //
//   Updated: 2024/11/19 19:20:06 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CM_CHUNK_H
# define CM_CHUNK_H

# include <stdint.h>

# define CM_CHUNK_SIZE		4096
# define CM_CHUNK_DATA_CAP	4064
# define CM_CHUNK_LINK_MAX	16

/* ************************************************************************** */

/**
 * @struct	s_chunk			Describes a memory chunk
 *
 * @uint32_t	(capacity)	Maximum capacity of the chunk.
 * @uint32_t	(size)		Actual size of the chunk.
 * @uint32_t	(alignment)	Alignment factor of the concerned data.
 * @uint32_t	(elem_size)	Element size.
 *
 * @s_flist		(free_list)	Free list head pointer.
 * @union
 *  @s_cm_chunk	(next)		Next linked chunk address.
 *  @uint64_t	(link)		Allowed number of static links.
 *
 * @uint8t[]	(data)		Data space.
 */
struct s_cm_chunk
{
	uint32_t			capacity;
	uint32_t			size;
	uint32_t			alignment;
	uint32_t			elem_size;
	struct s_flist		*free_list;
	union
	{
		struct s_cm_chunk	*next;
		uint64_t			link;
	};
	uint8_t				data[CM_CHUNK_DATA_CAP];
};

/* ************************************************************************** */

#endif
