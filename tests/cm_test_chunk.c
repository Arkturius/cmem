// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_test_chunk.c                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/06 21:58:01 by rgramati          #+#    #+#             //
//   Updated: 2024/11/19 19:08:33 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include <cmemtest.h>

#ifndef CM_INCLUDE_ALL
# define CM_INCLUDE_ALL
#endif
// #ifndef CM_CHUNK_IMPLEMENTATION
// # define CM_CHUNK_IMPLEMENTATION
// #endif
#include <cmem.h>

void	cm_test_result(uint32_t res, const char *test)
{
	if (!res)
	{
		PRINTF(
			CM_ANSI_BOLD CM_COLOR_PASSED
			"    [ Test passed ! ] > "
			CM_COLOR_TEXT
			"%s\n"
			CM_ANSI_RESET,
			test
		);
		return ;
	}
	PRINTF(
		CM_ANSI_BOLD CM_COLOR_WRONG
		"    [ Test FAILED ! ] > "
		CM_COLOR_TEXT
		"%s\n"
		CM_ANSI_RESET,
		test
	);
	exit(42);
}

uint32_t	assert_chunk_settings(
	struct s_cm_chunk	*chunk,
	uint32_t size,
	uint32_t elem_size,
	uint32_t capacity,
	uint32_t alignment
)	{
	return (
		chunk->size			!= size			||
		chunk->elem_size	!= elem_size	||
		chunk->capacity		!= capacity		||
		chunk->alignment	!= alignment
	);
}

typedef struct s_dummy32
{
	void	*dummy[4];
}	t_dummy32;

void	cm_arena_display(t_cm_arena *arena_ptr);
void	*cm_arena_alloc(t_cm_arena *arena_ptr, uint32_t size);
void	cm_arena_free(t_cm_arena *arena_ptr, void *ptr);

void	cm_unit_test_chunk(void)
{
	int					dummy[60] = {0, 1, 2, 3, 4, 5, 6, [58] = 7};
	int					dummy2[60];

	struct s_cm_chunk	chunks[3];
	struct s_cm_chunk	*current;

	current = cm_chunk_init(240, &chunks[0], 3);

	for (uint32_t i = 0; i < (current->capacity * 1) + 4; ++i)
	{
		cm_chunk_push(current, &dummy, sizeof(dummy));
	}

	cm_chunk_pop(current, 16);
	cm_memset(dummy2, -1, sizeof(dummy2));
	cm_chunk_push(current, &dummy2, sizeof(dummy2));
}
