/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:20 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:13 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "jpg_decode.h"
#include "huffman.h"
#include "stream.h"

t_ret	handle_huffman(t_stream *stream, t_jpg_data *data)
{
	uint8_t			table_head;
	t_huffman_node	**n;
	const uint8_t	*segment_end;

	segment_end = stream->current + stream_getw(stream) - 1;
	while (stream->current < segment_end)
	{
		table_head = stream_getc(stream);
		if ((table_head & 0xf0) == 0)
			n = &data->trees.dc[table_head & 0x0f];
		else
			n = &data->trees.ac[table_head & 0x0f];
		if (!(*n = new_huffman_tree(stream)))
			return (FAIL);
	}
	return (SUCCESS);
}
