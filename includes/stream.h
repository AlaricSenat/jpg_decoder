/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:16 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:12 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STREAM_H
# define STREAM_H

# include "fwd.h"

# include <stddef.h>

typedef struct	s_stream {
	const uint8_t			*current;
	const uint8_t *const	end;
	uint16_t				cache;
	unsigned				cached_bits;
	uint8_t					last_fetch_was_marker;
}				t_stream;

uint8_t			stream_getc(t_stream *stream);
uint16_t		stream_getw(t_stream *stream);
uint16_t		stream_getnbits(t_stream *stream, unsigned n);
void			stream_cache_align(t_stream *stream);

#endif
