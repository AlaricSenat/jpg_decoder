/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:17 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:17 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void		unexpected_eos(void)
{
	dprintf(2, "Unexpected end of stream\n");
	exit(1);
}

static uint8_t	s_getc(t_stream *stream)
{
	uint8_t	ret;

	if (stream->last_fetch_was_marker)
	{
		if (stream->current != stream->end && *stream->current == 0x00)
			++stream->current;
		stream->last_fetch_was_marker = 0;
	}
	if (stream->current == stream->end)
		unexpected_eos();
	ret = *stream->current++;
	if (ret == 0xff)
		stream->last_fetch_was_marker = 1;
	return (ret);
}

static void		cache_w(t_stream *stream)
{
	stream->cache = s_getc(stream);
	if (stream->current != stream->end)
	{
		stream->cache = (stream->cache << 8) | s_getc(stream);
		stream->cached_bits = 16;
	}
	else
		stream->cached_bits = 8;
}

uint16_t		stream_getnbits(t_stream *stream, unsigned bits)
{
	uint16_t	ret;

	assert(bits <= 16);
	ret = 0;
	while (bits--)
	{
		if (stream->cached_bits == 0)
			cache_w(stream);
		ret <<= 1;
		--stream->cached_bits;
		ret |= (stream->cache & (1 << stream->cached_bits))
			>> stream->cached_bits;
	}
	return (ret);
}

void			stream_cache_align(t_stream *stream)
{
	stream->cached_bits &= 0x8;
}
