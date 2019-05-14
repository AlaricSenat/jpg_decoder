/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:18 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:18 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream.h"

uint16_t		stream_getw(t_stream *stream)
{
	return (stream_getnbits(stream, 16));
}

uint8_t			stream_getc(t_stream *stream)
{
	return (stream_getnbits(stream, 8));
}
