/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_fetch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:19 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:13 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jpg_decode.h"
#include "stream.h"
#include "huffman.h"
#include "utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static uint8_t	fetch_code(t_stream *stream, const t_huffman_node *node)
{
	uint8_t	current_bit;

	while (node->right || node->left)
	{
		current_bit = stream_getnbits(stream, 1);
		if (!node)
		{
			dprintf(2, "invalid huffman tree");
			exit(-1);
		}
		if (current_bit)
			node = node->right;
		else
			node = node->left;
	}
	return (node->value);
}

static uint8_t	get_huff_id(uint8_t ids, t_tree_type type)
{
	if (type == DC)
		return ((ids & 0xf0) >> 4);
	return (ids & 0x0f);
}

static int16_t	get_table_value(uint8_t category, uint16_t code)
{
	uint16_t a;

	a = (1 << category) - 1;
	if ((code >> (category - 1)) & 1)
	{
		code ^= (1 << (category - 1));
		a &= (1 << (category - 1));
		return (a + code);
	}
	return (-a + code);
}

void			fetch_block(t_stream *s, const t_jpg_data *d,
					unsigned block_id, t_component *comp)
{
	uint8_t		f;
	unsigned	i;
	unsigned	zeroes;
	t_block		b;

	f = fetch_code(s, d->trees.dc[get_huff_id(comp->huffman_table_id, DC)]);
	comp->dc += get_table_value(f, stream_getnbits(s, f));
	b = comp->blocks[block_id];
	b[0] = comp->dc;
	i = 0;
	while (++i < BLOCK_ROW * BLOCK_ROW)
	{
		f = fetch_code(s, d->trees.ac[get_huff_id(comp->huffman_table_id, AC)]);
		if (!f)
		{
			memset(b + i, 0, (64 - i) * sizeof(int16_t));
			return ;
		}
		zeroes = (f & 0xf0) >> 4;
		memset(b + i, 0, zeroes * sizeof(int16_t));
		i += zeroes;
		f &= 0x0f;
		b[i] = get_table_value(f, stream_getnbits(s, f));
	}
}
