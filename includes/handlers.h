/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:07 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:11 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include "fwd.h"

typedef t_ret	(*t_handler)(t_stream *, t_jpg_data *);

t_ret			handle_sof(t_stream *stream, t_jpg_data *data);
t_ret			handle_sos(t_stream *stream, t_jpg_data *data);
t_ret			handle_qt(t_stream *stream, t_jpg_data *data);
t_ret			handle_huffman(t_stream *stream, t_jpg_data *data);

typedef struct	s_handler_pair
{
	uint8_t		code;
	t_handler	handler;
}				t_handler_pair;

t_ret			call_handler(t_stream *stream, t_jpg_data *data, uint8_t code);

#endif
