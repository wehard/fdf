/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:17:12 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 14:54:54 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_map(t_fdf_data *fdf_data)
{
	int			x;
	int			y;
	int			i;
	t_vertex	v[4];
	t_mat4x4	mvp;

	mvp = ft_create_mvp(fdf_data, fdf_data->map->pos, fdf_data->map->rot, fdf_data->map->scale);
	y = 0;
	while (y < fdf_data->map->h - 1)
	{
		x = 0;
		while (x < fdf_data->map->w - 1)
		{
			v[0] = fdf_data->map->verts[y * fdf_data->map->w + x];
			v[1] = fdf_data->map->verts[y * fdf_data->map->w + x + 1];
			v[2] = fdf_data->map->verts[(y + 1) * fdf_data->map->w + x];
			v[3] = fdf_data->map->verts[(y + 1) * fdf_data->map->w + x + 1];
			i = -1;
			while (++i < 4)
				v[i].pos = ft_transform_point(v[i].pos, mvp);
			draw_line(fdf_data->f_buf, v[0], v[1]);
			draw_line(fdf_data->f_buf, v[0], v[2]);
			if (x == fdf_data->map->w - 2)
				draw_line(fdf_data->f_buf, v[1], v[3]);
			if (y == fdf_data->map->h - 2)
				draw_line(fdf_data->f_buf, v[2], v[3]);
			x++;
		}
		y++;
	}
}
