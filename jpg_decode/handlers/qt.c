/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:26 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:13 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jpg_decode.h"
#include "stream.h"
#include "utils.h"

#include <stdlib.h>

static void	fill_table(t_stream *s, t_qt_table *qt)
{
	uint8_t	i;

	i = 0;
	while (i < 64)
	{
		if (qt->precision)
			qt->data[i++] = stream_getw(s);
		else
			qt->data[i++] = stream_getc(s);
	}
}

t_ret		handle_qt(t_stream *stream, t_jpg_data *data)
{
	uint8_t			info;
	t_qt_table		*curr;
	const uint8_t	*segment_end;

	segment_end = stream->current + stream_getw(stream) - 1;
	data->qt_tables_size = 0;
	while (stream->current < segment_end)
	{
		info = stream_getc(stream);
		if ((info & 0x0f) + 1 > data->qt_tables_size)
		{
			data->qt_tables_size = (info & 0x0f) + 1;
			if (!(data->qt_tables = realloc(data->qt_tables,
							data->qt_tables_size * sizeof(t_qt_table))))
				return (FAIL);
		}
		curr = &(data->qt_tables)[info & 0x0f];
		curr->precision = (info & 0xf0) >> 8;
		fill_table(stream, curr);
	}
	return (SUCCESS);
}
