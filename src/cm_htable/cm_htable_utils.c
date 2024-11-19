// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_htable_utils.c                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/11/17 22:47:31 by rgramati          #+#    #+#             //
//   Updated: 2024/11/17 23:40:30 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CM_HTABLE_IMPLEMENTATION
# define CM_HTABLE_IMPLEMENTATION
#endif
#include <cmem.h>

void	*cm_htable_at(t_cm_htable *htable_ptr, uint32_t index)
{
	struct s_cm_htable	*htable;
	void				*ptr;

	htable = htable_ptr;
	ptr = NULL;
	if (htable && index < htable->capacity)
		ptr = &htable->entries[index];
	return (ptr);
}

void	*cm_htable_get_data(void *entry_ptr)
{
	struct s_cm_entry	*entry;
	void				*ptr;

	entry = entry_ptr;
	ptr = NULL;
	if (entry)
		ptr = entry->data;
	return (ptr);
}
