/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:22:09 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:12 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUFFMAN_H
# define HUFFMAN_H

# include "fwd.h"

# include <stddef.h>

typedef struct s_huffman_node	t_huffman_node;

struct			s_huffman_node
{
	t_huffman_node	*left;
	t_huffman_node	*right;
	uint8_t			value;
};

typedef struct	s_huffman_trees {
	t_huffman_node	*dc[2];
	t_huffman_node	*ac[2];
}				t_huffman_trees;

typedef enum	e_tree_type {
	DC,
	AC
}				t_tree_type;

t_huffman_node	*new_huffman_tree(t_stream *stream);
t_ret			read_huffman_tables(t_stream *stream, t_jpg_data *data);
void			free_huffman_trees(t_huffman_trees *trees);

void			print_tree(t_huffman_node *root);

#endif
