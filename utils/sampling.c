/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:19 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:19 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include "jpg_decode.h"

uint8_t	block_count(const t_component *c)
{
	return (((c->sampling & 0xf0) >> 4) * (c->sampling & 0x0f));
}

uint8_t	hsampling(const t_component *c)
{
	return ((c->sampling & 0xf0) >> 4);
}

uint8_t	vsampling(const t_component *c)
{
	return (c->sampling & 0x0f);
}
