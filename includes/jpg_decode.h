/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_jpg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:14 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:12 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_JPG_H
# define PARSE_JPG_H

# include "fwd.h"

# include "huffman.h"

unsigned char	*parse_jpg(const char *path, unsigned *w, unsigned *h);

typedef struct	s_component {
	uint8_t		sampling;
	uint8_t		qt_table_id;
	uint8_t		huffman_table_id;
	int16_t		dc;
	t_block		*blocks;
	t_block		mcu;
}				t_component;

typedef struct	s_components {
	t_component	y;
	t_component	cb;
	t_component	cr;
}				t_components;

typedef struct	s_qt_table {
	uint8_t		precision;
	int16_t		data[64];
}				t_qt_table;

typedef struct	s_jpg_data {
	unsigned		w;
	unsigned		h;
	t_components	curr_components;
	uint8_t			qt_tables_size;
	t_qt_table		*qt_tables;
	t_huffman_trees	trees;

	unsigned		pixels_cursor;
	uint8_t			*pixels;
}				t_jpg_data;

typedef struct	s_rgb {
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}				t_rgb;

typedef struct	s_zigzag_data
{
	unsigned x;
	unsigned y;
	unsigned reverse;
	unsigned cursor;
}				t_zigzag_data;

void			decode_component(t_stream *stream, t_jpg_data *data);
void			fetch_block(t_stream *stream, const t_jpg_data *data,
					unsigned block_id, t_component *component);
void			zigzag(t_block b);
void			apply_inv_dct(t_block block);
void			insert_colors(t_jpg_data *data);

#endif
