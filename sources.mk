# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 22:57:06 by rgramati          #+#    #+#              #
#    Updated: 2024/11/27 23:02:50 by rgramati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CM_CHUNK_DIR	:=	cm_chunk
CM_HTABLE_DIR	:=	cm_htable
CM_ARENA_DIR	:=	cm_arena
CM_LIMG_DIR		:=	cm_limg

CM_CHUNK_SRC	:=	cm_chunk.c			\
					cm_links.c			\
					cm_chunk_utils.c	\

CM_HTABLE_SRC	:=	cm_htable.c			\
					cm_htable_utils.c	\

CM_ARENA_SRC	:=	cm_arena.c			\

CM_LIMG_SRC		:=	cm_limg.c			\

CM_CHUNK_SRC	:=	$(addprefix $(CM_CHUNK_DIR)/, $(CM_CHUNK_SRC))
CM_HTABLE_SRC	:=	$(addprefix $(CM_HTABLE_DIR)/, $(CM_HTABLE_SRC))
CM_ARENA_SRC	:=	$(addprefix $(CM_ARENA_DIR)/, $(CM_ARENA_SRC))
CM_LIMG_SRC		:=	$(addprefix $(CM_LIMG_DIR)/, $(CM_LIMG_SRC))

SRCS			:=	$(CM_CHUNK_SRC) $(CM_HTABLE_SRC) $(CM_ARENA_SRC) $(CM_LIMG_SRC)
