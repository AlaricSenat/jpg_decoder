/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:19 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:19 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

t_ret	map_file(const char *path, t_map *map)
{
	int			fd;
	struct stat	stat;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (FAIL);
	if ((fstat(fd, &stat)) == -1)
		return (FAIL);
	map->size = stat.st_size;
	map->map = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map->map == MAP_FAILED)
		return (FAIL);
	return (SUCCESS);
}

void	unmap_file(t_map *map)
{
	munmap(map->map, map->size);
}
