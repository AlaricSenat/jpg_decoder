/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:17 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:17 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jpg_decode.h"
#include "utils.h"

#include <string.h>

static void	get_cbcr_from_y(const t_jpg_data *data, unsigned y_pos,
		uint16_t *cr, uint16_t *cb)
{
	unsigned y_blocks_count;
	unsigned pos;

	y_blocks_count = block_count(&data->curr_components.y);
	pos = y_pos / (y_blocks_count / block_count(&data->curr_components.cr));
	*cr = data->curr_components.cr.mcu[pos];
	pos = y_pos / (y_blocks_count / block_count(&data->curr_components.cb));
	*cb = data->curr_components.cb.mcu[pos];
}

static void	get_rgb(const t_jpg_data *data, unsigned y_pos, t_rgb *rgb)
{
	uint16_t y;
	uint16_t cr;
	uint16_t cb;

	y = data->curr_components.y.mcu[y_pos];
	get_cbcr_from_y(data, y_pos, &cr, &cb);
	rgb->r = clip(y + 1.402 * (cr - 128));
	rgb->g = clip(y - 0.34414 * (cb - 128) - 0.71414 * (cr - 128));
	rgb->b = clip(y + 1.772 * (cb - 128));
}

void		insert_colors(t_jpg_data *d)
{
	t_rgb			rgb;
	unsigned		y_pos;
	unsigned		x;
	unsigned		y;
	const unsigned	w = hsampling(&d->curr_components.y) * 8;

	y_pos = 0;
	x = 0;
	y = 0;
	while (y_pos < 64 * block_count(&d->curr_components.y))
	{
		get_rgb(d, y_pos, &rgb);
		memcpy(d->pixels + d->pixels_cursor + (y * d->w + x) * 3, &rgb, 3);
		++y_pos;
		++x;
		if (!(y_pos % w))
		{
			++y;
			x -= w;
		}
	}
	d->pixels_cursor += w * 3;
	if (!(d->pixels_cursor % (d->w * 3)))
		d->pixels_cursor += (8 * vsampling(&d->curr_components.y) - 1)
			* d->w * 3;
}
