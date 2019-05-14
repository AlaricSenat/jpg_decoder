/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:17 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:12 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "fwd.h"

# include <stddef.h>

uint8_t			block_count(const t_component *c);
uint8_t			hsampling(const t_component *c);
uint8_t			vsampling(const t_component *c);

typedef struct	s_map
{
	uint8_t	*map;
	size_t	size;
}				t_map;

t_ret			map_file(const char *path, t_map *map);
void			unmap_file(t_map *map);

uint8_t			clip(int a);

#endif
