/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sof.c                                              :+:      :+:    :+:   */
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

static t_ret	comp_alloc(t_component *c)
{
	unsigned block_c;

	block_c = block_count(c);
	if (!(c->blocks = malloc(block_c * sizeof(t_block*))))
		return (FAIL);
	if (!(c->mcu = malloc(block_c * sizeof(int16_t) * 64)))
		return (FAIL);
	while (block_c--)
	{
		if (!(c->blocks[block_c] = malloc(sizeof(int) * 64)))
			return (FAIL);
	}
	return (SUCCESS);
}

t_ret			handle_sof(t_stream *stream, t_jpg_data *data)
{
	uint8_t		comp_nb;
	t_component	*c;

	stream_getw(stream);
	stream_getc(stream);
	data->h = stream_getw(stream);
	data->w = stream_getw(stream);
	comp_nb = stream_getc(stream);
	while (comp_nb--)
	{
		c = ((t_component*)&data->curr_components) + stream_getc(stream) - 1;
		c->sampling = stream_getc(stream);
		c->qt_table_id = stream_getc(stream);
		if (comp_alloc(c) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}
