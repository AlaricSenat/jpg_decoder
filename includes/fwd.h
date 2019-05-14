/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fwd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:00 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:40:11 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FWD_H
# define FWD_H

# include <stdint.h>

# define BLOCK_ROW (8u)
# define BLOCK_COL (8u)

typedef int16_t	*t_block;

typedef uint8_t	t_ret;
# define SUCCESS (0u)
# define FAIL (1u)

typedef struct s_jpg_data		t_jpg_data;

typedef struct s_stream			t_stream;

typedef struct s_component		t_component;
typedef struct s_components		t_components;

typedef struct s_huffman_node	t_huffman_node;
typedef struct s_huffman_trees	t_huffman_trees;
#endif
