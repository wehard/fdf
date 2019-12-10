/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:15:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/10 15:15:56 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_get_next_line.h"
#include "fdf.h"

t_map *create_map(int w, int h)
{
	t_map *map;
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
	ft_bzero(map->verts, sizeof(t_vertex) * size);
	return (map);
}

static int	free_map_list(t_list *list)
{
	ft_putendl("destroying map list");
	if (!list)
	{
		ft_putendl("list was null!");
		return (0);
	}
	while (list)
	{
		free(list->content);
		list = list->next;
	}
	return (0);
}

void	init_map(t_map *map, t_rgba low, t_rgba high)
{
	int x;
	int y;
	float x_offset;
	float z_offset;

	x_offset = ((float)map->w / 2) - 0.5f;
	z_offset = ((float)map->h / 2) - 0.5f;
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			map->verts[y * map->w + x].pos.x -= x_offset;
			map->verts[y * map->w + x].pos.z -= z_offset;
			map->verts[y * map->w + x].col = ft_lerp_rgba(low, high, ft_convert_range(map->verts[y * map->w + x].pos.y, map->h_min, map->h_max, 0.0f, 1.0f));
			x++;
		}
		y++;
	}
}

t_map *read_to_map(int w, int h, t_list *lst)
{
	t_list *current;
	t_map *map;
	char **points;
	int x;
	int y;
	int ch;

	if (!(map = create_map(w, h)))
		return (NULL);
	y = 0;
	current = lst;
	while (y < h)
	{
		points = ft_strsplit((char*)current->content, ' ');
		x = 0;
		while (*points)
		{
			ch = ft_atoi(*points);
			if (ch > map->h_max)
				map->h_max = ch;
			if (ch < map->h_min)
				map->h_min = ch;
			map->verts[y * map->w + x] = make_vertex(x, ch, y, ft_make_rgba(1.0f, 1.0f, 1.0f, 1.0f));
			points++;
			x++;
		}
		y++;
		current = current->next;
	}
	init_map(map, RED, WHITE);
	free_map_list(lst);
	return (map);
}

int	read_map_data(int fd, t_map **map)
{
	t_list *lst;
	t_list *temp;
	int		width;
	int		height;
	char	*line;

	lst = NULL;
	width = -1;
	height = 0;
	while (ft_get_next_line(fd, &line))
	{
		if (width == -1)
			width = ft_nwords(line, ' ');
		if (!(temp = ft_lstnew(line, ft_strlen(line) + 1)))
			return (free_map_list(lst));
		if (ft_nwords(line, ' ') != width)
			return (free_map_list(lst));
		ft_lstappend(&lst, temp);
		height++;
		free(line);
	}
	*map = read_to_map(width, height, lst);
	return (1);
}


