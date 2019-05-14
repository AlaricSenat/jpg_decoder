/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:17 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:17 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"
#include "stream.h"

#include "jpg_decode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static t_ret	add_node(uint16_t code, unsigned code_size,
		uint8_t value, t_huffman_node **root)
{
	if (!*root)
		if (!(*root = calloc(1, sizeof(t_huffman_node))))
			return (FAIL);
	if (code_size-- == 0)
	{
		(*root)->value = value;
		return (SUCCESS);
	}
	if ((code >> code_size) & 1)
		return (add_node(code, code_size, value, &(*root)->right));
	return (add_node(code, code_size, value, &(*root)->left));
}

static void		free_node(t_huffman_node *node)
{
	if (!node)
		return ;
	if (node->right)
		free_node(node->right);
	if (node->left)
		free_node(node->left);
	free(node);
}

void			free_huffman_trees(t_huffman_trees *trees)
{
	free_node(trees->dc[0]);
	free_node(trees->dc[1]);
	free_node(trees->ac[0]);
	free_node(trees->ac[1]);
}

t_huffman_node	*new_huffman_tree(t_stream *stream)
{
	t_huffman_node	*ret;
	uint8_t			codes[16];
	uint16_t		code;
	unsigned		i;
	unsigned		j;

	ret = NULL;
	code = 0;
	i = -1;
	while (++i < 16)
		codes[i] = stream_getc(stream);
	i = -1;
	while (++i < 16)
	{
		j = codes[i];
		while (j--)
			if (add_node(code++, i + 1, stream_getc(stream), &ret) == FAIL)
			{
				if (ret)
					free_node(ret);
				return (NULL);
			}
		code <<= 1;
	}
	return (ret);
}
