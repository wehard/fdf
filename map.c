/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:15:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/29 23:58:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_get_next_line.h"
#include "fdf.h"
#include "point.h"

t_v_map *create_v_map(int w, int h)
{
	t_v_map *v_map;
	int		size;

	size = w * h;
	if (!(v_map = (t_v_map*)malloc(sizeof(t_v_map))))
		return (NULL);
	v_map->size = size;
	v_map->w = w;
	v_map->h = h;
	v_map->pos.x = 0.0f;
	v_map->pos.y = 0.0f;
	v_map->pos.z = 0.0f;
	v_map->rot.x = 0.0f;
	v_map->rot.y = 0.0f;
	v_map->rot.z = 0.0f;
	if (!(v_map->v = (t_vec3*)malloc(sizeof(t_vec3) * size)))
		return (NULL);
	ft_bzero(v_map->v, sizeof(t_vec3) * size);
	return (v_map);
}

t_v_map *read_to_v_map(int w, int h, t_list *lst)
{
	t_list *current;
	t_v_map *v_map;
	char **points;
	int x;
	int y;

	if (!(v_map = create_v_map(w, h)))
		return (NULL);
	y = 0;
	current = lst;
	while (y < h)
	{
		points = ft_strsplit((char*)current->content, ' ');
		x = 0;
		while (*points)
		{
			v_map->v[y * v_map->w + x] = make_vec3_pos(x, y, ft_atoi(*points));
			points++;
			x++;
		}
		y++;
		current = current->next;
	}
	return (v_map);
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

int	read_map_data(int fd, t_v_map **map)
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
	*map = read_to_v_map(width, height, lst);
	return (1);
}
