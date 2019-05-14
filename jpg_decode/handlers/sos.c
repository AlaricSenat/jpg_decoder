/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:16 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:16 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "jpg_decode.h"
#include "stream.h"
#include "utils.h"

#include <stdlib.h>

t_ret	decode_img(t_stream *stream, t_jpg_data *d)
{
	unsigned	components_count;

	components_count = (d->w * d->h) / 64 + ((d->w * d->h) % 64 ? 1 : 0);
	components_count /= block_count(&d->curr_components.y);
	if (!d->pixels)
		d->pixels = calloc((d->w * d->h) * 3, sizeof(uint8_t));
	if (!d->pixels)
		return (FAIL);
	while (components_count--)
	{
		decode_component(stream, d);
		insert_colors(d);
	}
	stream_cache_align(stream);
	return (SUCCESS);
}

t_ret	handle_sos(t_stream *stream, t_jpg_data *data)
{
	uint8_t		comp_nb;
	t_component	*c;

	stream_getw(stream);
	comp_nb = stream_getc(stream);
	while (comp_nb--)
	{
		c = ((t_component*)&data->curr_components) + stream_getc(stream) - 1;
		c->huffman_table_id = stream_getc(stream);
	}
	stream_getw(stream);
	stream_getc(stream);
	return (decode_img(stream, data));
}
