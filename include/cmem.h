// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cmem.h                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/06 00:35:57 by rgramati          #+#    #+#             //
//   Updated: 2024/11/24 13:43:18 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CMEM_H
# define CMEM_H

# include <stdint.h>
# include <unistd.h>

# ifdef CM_INCLUDE_ALL
#  ifndef CM_CHUNK_IMPLEMENTATION
#   define CM_CHUNK_IMPLEMENTATION
#  endif
#  ifndef CM_ARENA_IMPLEMENTATION
#   define CM_ARENA_IMPLEMENTATION
#  endif
#  ifndef CM_HTABLE_IMPLEMENTATION
#   define CM_HTABLE_IMPLEMENTATION
#  endif
#  ifndef CM_LIMG_IMPLEMENTATION
#   define CM_LIMG_IMPLEMENTATION
#  endif
# endif

# ifdef CM_CHUNK_IMPLEMENTATION
#  include <../src/cm_chunk/cm_chunk.h>
# endif

# ifdef CM_ARENA_IMPLEMENTATION
#  include <../src/cm_arena/cm_arena.h>
# endif

# ifdef CM_HTABLE_IMPLEMENTATION
#  include <../src/cm_htable/cm_htable.h>
# endif

# ifdef CM_LIMG_IMPLEMENTATION
#  include <../src/cm_limg/cm_limg.h>
# endif

# define CM_BIT_COUNT	"\
\x00\x00\x01\x00\x02\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\
\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

/**
 * @enum	e_chunk_flags
 *
 * 	CM_CLEAR_ZERO : clear structure data space.
 *	CM_CLEAR_NULL : reset structure settings.
 *	CM_CLEAR_FREE : frees the structure.
 *					is also CM_CLEAR_ZERO | CM_CLEAR_NULL
 */
enum	e_clear_flags
{
	CM_CLEAR_ZERO = 1 << 8,
	CM_CLEAR_NULL = 1 << 9,
	CM_CLEAR_STATIC = 1 << 10,
	CM_CLEAR_FREE = CM_CLEAR_ZERO | CM_CLEAR_NULL | 1 << 11
};

/**
 * @struct	s_flist			Free list linked pointer.
 *
 * @struct s_flist *	(next)	Next pointer.
 */
struct s_flist
{
	struct s_flist	*next;
};

// ************************************************************************** //
# ifdef CM_CHUNK_IMPLEMENTATION

typedef void				t_cm_chunk;

/**
 * @brief	Init a memory chunk.
 *
 * @param		(elem_size)	Element size, pass sizeof(elem) to setup correctly.
 * @param		(ptr)		If not null, use this as address.
 * @param		(link)		Allowed number of links in a chunk array.
 *
 * @returns	A pointer to a memory chunk.
 */
t_cm_chunk
*cm_chunk_init(uint32_t elem_size, void *ptr, uint64_t link);

	/**
 * @brief	Perform clear operations on a memory chunk.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(flags)		Combination of e_chunk_flags.
 */
void
cm_chunk_clear(t_cm_chunk *chunk_ptr, uint32_t flags);

/**
 * @brief	Allocate space on a memory chunk for a new element.
 *
 * @param		(chunk)		Chunk pointer.
 *
 * @returns	A pointer to the allocated space.
 */
void
*cm_chunk_alloc(t_cm_chunk *chunk_ptr);

/**
 * @brief	Pushes an element on a memory chunk.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(elem)		Opaque pointer to source data.
 * @param		(elem_size)	Element size of source.
 *
 * @note	A safe way to use this is by passing both the adress and the size
 *			of a static object.
 *			cm_chunk_push(example_chunk, &object, sizeof(object));
 *
 * @returns A pointer to the pushed element.
 */
void
*cm_chunk_push(t_cm_chunk *chunk_ptr, void *elem, uint32_t elem_size);

/**
 * @brief	Free space from a memory chunk using an index.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(index)		Index of the element to pop.
 */
void
cm_chunk_pop(t_cm_chunk *chunk_ptr, uint32_t index);

/**
 * @brief	Get the element at a certain index on a memory chunk.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(index)		The index.
 *
 * @returns	A pointer to this element (depending on chunk alignment);
 */
void
*cm_chunk_at(t_cm_chunk *chunk_ptr, uint32_t index);

/**
 * @brief	Get an element index from its address.
 *
 * @param		(chunk)		Chunk pointer.
 * @param		(elem)		The element.
 *
 * @returns	The index of elem in the chunk.
 * @note	Will return ((uint32_t)-1) if the adress is not aligned with
 *			chunk settings nor in this chunk.
 */
uint32_t
cm_chunk_index(t_cm_chunk *chunk_ptr, void *elem);

/**
 * @brief	Get chunk size.
 *
 * @param		(chunk)		Chunk pointer.
 * 
 * @returns	Chunk actual size.
 */
uint32_t
cm_chunk_size(t_cm_chunk *chunk_ptr);

/**
 * @brief	Returns the next chunk pointer.
 *
 * @param		(chunk)		Chunk pointer.
 *
 * @return	Next chunk pointer, NULL if no linking | static linking
 */
t_cm_chunk	*cm_chunk_next(t_cm_chunk *chunk_ptr);

/**
 * @brief	Allocates new linked chunk for additional space.
 *
 * @param		(chunk)		Chunk pointer.
 * 
 * @return	Next chunk pointer.
 */
t_cm_chunk	*cm_chunk_link(t_cm_chunk *chunk_ptr);

# endif	//	CM_CHUNK_IMPLEMENTATION

// ************************************************************************** //

#ifdef CM_ARENA_IMPLEMENTATION

typedef void				t_cm_arena;

t_cm_arena
*cm_arena_init();

void
cm_arena_clear(t_cm_arena *arena_ptr, uint32_t flags);

#endif

// ************************************************************************** //

#ifdef CM_HTABLE_IMPLEMENTATION

typedef void				t_cm_htable;

/**
 * @brief	Init a Hash table
 *
 * @param		(capacity)	Number of elements;
 * @param		(ptr)		If not null, use this as address.
 *
 * @returns	A pointer to a Hash table
 */
t_cm_htable
*cm_htable_init(uint32_t capacity, void *ptr);

void
cm_htable_clear(t_cm_htable *htable_ptr, uint32_t flags);

void
cm_htable_set(t_cm_htable *htable_ptr, const char *key, void *data);

void
*cm_htable_get(t_cm_htable *htable_ptr, const char *key);

void
*cm_htable_remove(t_cm_htable *htable_ptr, const char *key);

void
*cm_htable_at(t_cm_htable *htable_ptr, uint32_t index);

void
*cm_htable_get_data(void *entry_ptr);

uint32_t
cm_djb2(const char *key);

#endif

// ************************************************************************** //

#ifdef CM_LIMG_IMPLEMENTATION

typedef enum e_open_types
{
	CM_OPEN_LOAD = 1,
	CM_OPEN_SAVE = 1 << 1,
	CM_OPEN_ALLOC = 1 << 2
}	t_open_types;

uint32_t
cm_bmp(const char *filename, uint32_t **data_ptr, uint64_t flags);

// TODO : #include <zlib.h> and png parsing :)

#endif

// ************************************************************************** //

uint32_t
cm_pow2next(uint32_t x);

uint32_t
cm_min(uint32_t a, uint32_t b);

uint32_t
cm_strlen(const char *str);

int32_t
cm_strcmp(const char *s1, const char *s2);

char
*cm_strdup(const char *str);

void
cm_memset(void *ptr, unsigned char c, uint32_t n);

void
cm_memcpy(void *dst, void *src, uint32_t n);

void
cm_memmove(void *dst, void *src, uint32_t n);

/* ************************************************************************** */

#endif
