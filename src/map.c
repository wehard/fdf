/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:15:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/13 12:58:24 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_get_next_line.h"
#include "fdf.h"

static int		free_map_list(t_list *list)
{
	t_list *tmp;

	if (!list)
	{
		ft_putendl("map: list was null!");
		return (0);
	}
	while (list)
	{
		tmp = list;
		free(tmp->content);
		list = tmp->next;
		free(tmp);
	}
	return (0);
}

static int		free_temp_and_line(t_list *temp, char *line)
{
	free(line);
	free(temp->content);
	free(temp);
	return (0);
}

static void		init_map(t_map *map, t_rgba c1, t_rgba c2)
{
	t_intvec2	c;
	float		x_offset;
	float		z_offset;

	calculate_map_minmax(map);
	x_offset = ((float)map->w / 2) - 0.5f;
	z_offset = ((float)map->h / 2) - 0.5f;
	c.y = 0;
	while (c.y < map->h)
	{
		c.x = 0;
		while (c.x < map->w)
		{
			map->verts[c.y * map->w + c.x].pos.x -= x_offset;
			map->verts[c.y * map->w + c.x].pos.z -= z_offset;
			map->verts[c.y * map->w + c.x].col = ft_lerp_rgba(c1, c2,
				ft_inverse_lerp(map->verts[c.y * map->w + c.x].pos.y,
				map->h_min, map->h_max));
			c.x++;
		}
		c.y++;
	}
}

static t_map	*list_to_map(t_map *map, t_list *lst)
{
	t_list		*current;
	char		**points;
	t_intvec2	cur;

	cur.y = 0;
	current = lst;
	while (cur.y < map->h)
	{
		points = ft_strsplit((char*)current->content, ' ');
		cur.x = 0;
		while (cur.x < map->w)
		{
			map->verts[cur.y * map->w + cur.x] =
				make_vertex(cur.x, ft_atoi(points[cur.x]), cur.y, WHITE);
			free(points[cur.x]);
			cur.x++;
		}
		free(points);
		cur.y++;
		current = current->next;
	}
	free_map_list(lst);
	return (map);
}

int				read_map_file(int fd, t_map **map, t_rgba c1, t_rgba c2)
{
	t_list		*lst;
	t_list		*temp;
	t_intvec2	size;
	char		*line;

	lst = NULL;
	size.x = -1;
	size.y = 0;
	while (ft_get_next_line(fd, &line))
	{
		if (size.x == -1)
			size.x = ft_nwords(line, ' ');
		if (!(temp = ft_lstnew(line, ft_strlen(line) + 1)))
			return (free_map_list(lst));
		if (ft_nwords(line, ' ') != size.x)
			return (free_map_list(lst) || free_temp_and_line(temp, line));
		ft_lstappend(&lst, temp);
		size.y++;
		free(line);
	}
	if (!(*map = create_map(size.x, size.y)))
		return (0);
	list_to_map(*map, lst);
	init_map(*map, c1, c2);
	return (1);
}
