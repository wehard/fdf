/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:06:06 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/12 13:12:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*create_map(int w, int h)
{
	t_map	*map;
	int		size;

	size = w * h;
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	map->size = size;
	map->w = w;
	map->h = h;
	map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	map->rot = make_vec3_rot(0.0f, 0.0f, 0.0f);
	map->h_max = INT32_MIN;
	map->h_min = INT32_MAX;
	if (!(map->verts = (t_vertex*)malloc(sizeof(t_vertex) * size)))
		return (NULL);
	return (map);
}

void	calculate_map_minmax(t_map *map)
{
	t_intvec2 c;

	c.y = 0;
	while (c.y < map->h)
	{
		c.x = 0;
		while (c.x < map->w)
		{
			if (map->verts[c.y * map->w + c.x].pos.y > map->h_max)
				map->h_max = map->verts[c.y * map->w + c.x].pos.y;
			if (map->verts[c.y * map->w + c.x].pos.y < map->h_min)
				map->h_min = map->verts[c.y * map->w + c.x].pos.y;
			c.x++;
		}
		c.y++;
	}
}
