/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jpg_decode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:17 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:17 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jpg_decode.h"

#include "huffman.h"
#include "stream.h"
#include "handlers.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void		free_data(t_jpg_data *dat)
{
	t_component	*c;
	unsigned	i;
	unsigned	blocks_c;

	i = 0;
	while (i < 3)
	{
		c = ((t_component*)&dat->curr_components) + i++;
		blocks_c = block_count(c);
		while (blocks_c--)
			free(c->blocks[blocks_c]);
		free(c->blocks);
		free(c->mcu);
	}
	free(dat->qt_tables);
	free_huffman_trees(&dat->trees);
}

static uint8_t	*return_jpg(t_map *map, unsigned *w, unsigned *h,
		t_jpg_data *dat)
{
	free_data(dat);
	unmap_file(map);
	*w = dat->w;
	*h = dat->h;
	return (dat->pixels);
}

unsigned char	*jpg_decode(const char *path, unsigned *w, unsigned *h)
{
	t_map		map;
	t_jpg_data	data;
	t_stream	stream;

	if (map_file(path, &map) == FAIL)
	{
		perror("can't map jpg");
		return (NULL);
	}
	stream = (t_stream){map.map, map.map + map.size, 0, 0, 0};
	memset(&data, 0, sizeof(data));
	while (stream.current < stream.end)
	{
		if (stream_getc(&stream) != 0xff)
			continue;
		if (call_handler(&stream, &data, stream_getc(&stream)) == FAIL)
			return (return_jpg(&map, w, h, &data));
	}
	return (return_jpg(&map, w, h, &data));
}
