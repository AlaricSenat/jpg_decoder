/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:18 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:13 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jpg_decode.h"
#include "stream.h"
#include "huffman.h"
#include "utils.h"

#include <string.h>

void		decode_block(t_stream *stream, const t_jpg_data *data,
				unsigned block_id, t_component *component)
{
	unsigned			i;
	const t_qt_table	*qt;

	i = 0;
	fetch_block(stream, data, block_id, component);
	qt = &data->qt_tables[component->qt_table_id];
	while (i < 64)
	{
		component->blocks[block_id][i] *= qt->data[i];
		++i;
	}
	zigzag(component->blocks[block_id]);
	apply_inv_dct(component->blocks[block_id]);
}

static void	cpy_block(unsigned i, unsigned j, const t_block b, t_component *c)
{
	unsigned	y;

	y = -1;
	while (++y < 8)
	{
		memcpy(c->mcu + i * hsampling(c) * 64 + y * hsampling(c) * 8 + j * 8,
				b + 8 * y,
				sizeof(int16_t) * 8);
	}
}

static void	make_mcu(t_component *c)
{
	t_block		*b;
	unsigned	i;
	unsigned	j;

	i = -1;
	b = c->blocks;
	while (++i < vsampling(c))
	{
		j = -1;
		while (++j < hsampling(c))
			cpy_block(i, j, *b++, c);
	}
}

void		decode_component(t_stream *stream, t_jpg_data *data)
{
	t_component	*comp;
	unsigned	i;
	unsigned	block_id;

	i = 0;
	while (i < 3)
	{
		comp = ((t_component*)&data->curr_components) + i++;
		block_id = 0;
		while (block_id < block_count(comp))
			decode_block(stream, data, block_id++, comp);
		make_mcu(comp);
	}
}
