/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:19 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:19 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jpg_decode.h"
#include "stream.h"

int main() {
	const uint16_t data = 0b1110101110101011;
	t_stream s = {(const uint8_t*)&data, (const uint8_t*)(&data)+ 2, 0, 0, 0};

	uint16_t b = stream_getnbits(&s, 8);
	if (b != 0b10101011)
		return (-1);
	b = stream_getnbits(&s, 8);
	if (b != 0b11101011)
		return (-1);
	return (0);
}
