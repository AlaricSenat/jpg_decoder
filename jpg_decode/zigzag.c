/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zigzag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:18 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:18 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jpg_decode.h"

#include <string.h>

static void	diag(const t_block b, t_block dst, t_zigzag_data *data)
{
	static const unsigned	limit = BLOCK_ROW - 1;
	int						ascend;
	unsigned				x;
	unsigned				y;

	ascend = (data->reverse) ? (data->y & 1) : !(data->x & 1);
	x = data->x;
	y = data->y;
	while (1)
	{
		dst[y * BLOCK_ROW + x] = b[data->cursor++];
		x += ascend ? 1 : -1;
		y += ascend ? -1 : 1;
		if (limit - x > limit || limit - y > limit)
			break ;
		data->x = x;
		data->y = y;
	}
}

void		zigzag(t_block b)
{
	int16_t			tmp[BLOCK_ROW * BLOCK_ROW];
	t_zigzag_data	data;

	memset(&data, 0, sizeof(t_zigzag_data));
	while (data.x < BLOCK_ROW - 1 || data.y < BLOCK_ROW - 1)
	{
		diag(b, tmp, &data);
		if (data.reverse)
			++data.y;
		else
			++data.x;
		diag(b, tmp, &data);
		if (data.y == 7)
			data.reverse = 1;
		if (data.reverse)
			++data.x;
		else
			++data.y;
	}
	memcpy(b, tmp, sizeof(tmp) - sizeof(int16_t));
}
