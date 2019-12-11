/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:17:12 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 17:18:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_quad(t_fdf_data *fdf_data, t_mat4x4 mvp, t_quad q, t_intvec2 p)
{
	q.a.pos = ft_transform_point(q.a.pos, mvp);
	q.b.pos = ft_transform_point(q.b.pos, mvp);
	q.c.pos = ft_transform_point(q.c.pos, mvp);
	q.d.pos = ft_transform_point(q.d.pos, mvp);
	draw_line(fdf_data->f_buf, q.a, q.b);
	draw_line(fdf_data->f_buf, q.a, q.c);
	if (p.x == fdf_data->map->w - 2)
		draw_line(fdf_data->f_buf, q.b, q.d);
	if (p.y == fdf_data->map->h - 2)
		draw_line(fdf_data->f_buf, q.c, q.d);
}

void		ft_draw_map(t_fdf_data *fdf_data)
{
	int			x;
	int			y;
	int			i;
	t_quad		q;
	t_mat4x4	mvp;

	mvp = ft_create_mvp(fdf_data, fdf_data->map->pos,
		fdf_data->map->rot, fdf_data->map->scale);
	y = 0;
	while (y < fdf_data->map->h - 1)
	{
		x = 0;
		while (x < fdf_data->map->w - 1)
		{
			q.a = fdf_data->map->verts[y * fdf_data->map->w + x];
			q.b = fdf_data->map->verts[y * fdf_data->map->w + x + 1];
			q.c = fdf_data->map->verts[(y + 1) * fdf_data->map->w + x];
			q.d = fdf_data->map->verts[(y + 1) * fdf_data->map->w + x + 1];
			draw_quad(fdf_data, mvp, q, make_intvec2(x, y));
			x++;
		}
		y++;
	}
}
