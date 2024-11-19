// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cm_htable.h                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/10/06 19:06:48 by rgramati          #+#    #+#             //
//   Updated: 2024/11/18 18:31:47 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CM_HTABLE_H
# define CM_HTABLE_H

# include <stdint.h>

# define CM_HTABLE_BASE_CAP	32
# define CM_HTABLE_MAX_CAP	1024

// ************************************************************************** //

struct s_cm_entry
{
	char	*key;
	void	*data;
};

struct s_cm_htable
{
	struct s_cm_entry	*entries;
	void				(*del)(void *);
	uint64_t			size;
	uint64_t			capacity;
};

// ************************************************************************** //

#endif
