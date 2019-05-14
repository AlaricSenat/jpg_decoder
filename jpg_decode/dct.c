/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:17 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:12 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jpg_decode.h"
#include "utils.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>

static float	dct_c(int x)
{
	return (x == 0 ? 0.7071 : 1.);
}

static int16_t	inv_dtc(unsigned x, unsigned y, const t_block block)
{
	float				sum;
	unsigned			i;
	unsigned			j;
	static const float	cos_tab[BLOCK_ROW][BLOCK_COL] = {
		{1., 0.9807, 0.9238, 0.8314, 0.7071, 0.5555, 0.3826, 0.1950},
		{1., 0.8314, 0.3826, -0.1950, -0.7071, -0.9807, -0.9238, -0.5555},
		{1., 0.5555, -0.3826, -0.9807, -0.7071, 0.1950, 0.9238, 0.8314},
		{1., 0.1950, -0.9238, -0.5555, 0.7071, 0.8314, -0.3826, -0.9807},
		{1., -0.1950, -0.9238, 0.5555, 0.7071, -0.8314, -0.3826, 0.9807},
		{1., -0.5555, -0.3826, 0.9807, -0.7071, -0.1950, 0.9238, -0.8314},
		{1., -0.8314, 0.3826, 0.1950, -0.7071, 0.9807, -0.9238, 0.5555},
		{1., -0.9807, 0.9238, -0.8314, 0.7071, -0.5555, 0.3826, -0.1950},
	};

	sum = 0.;
	i = -1;
	while (++i < BLOCK_ROW)
	{
		j = -1;
		while (++j < BLOCK_COL)
			sum += dct_c(i) * dct_c(j) * block[i * BLOCK_ROW + j] *
				cos_tab[x][i] * cos_tab[y][j];
	}
	return (round(sum / 4.));
}

void			apply_inv_dct(t_block block)
{
	int16_t		res[64];
	unsigned	x;
	unsigned	y;

	x = -1;
	while (++x < BLOCK_ROW)
	{
		y = -1;
		while (++y < BLOCK_COL)
			res[x * BLOCK_ROW + y] = clip(inv_dtc(x, y, block) + 128);
	}
	memcpy(block, res, 64 * sizeof(int16_t));
}
