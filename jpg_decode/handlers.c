/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:17 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:17 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "jpg_decode.h"
#include "stream.h"

t_ret	call_handler(t_stream *stream, t_jpg_data *data, uint8_t code)
{
	const static t_handler_pair	pairs[] = {
		{0xc0, handle_sof}, {0xc4, handle_huffman},
		{0xda, handle_sos}, {0xdb, handle_qt}};
	unsigned					i;

	i = -1;
	while (++i < 4)
		if (pairs[i].code == code)
			return (pairs[i].handler(stream, data));
	return (SUCCESS);
}
