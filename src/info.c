/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:04:16 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/12 14:38:47 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"
#include "mlx.h"

void	ft_draw_axis(t_fdf_data *fdf_data, t_vec3 pos, t_vec3 rot, float scale)
{
	t_mat4x4 mvp;
	t_vertex origin;
	t_vertex xaxis;
	t_vertex yaxis;
	t_vertex zaxis;

	origin = make_vertex(0.0f, 0.0f, 0.0f, WHITE);
	xaxis = make_vertex(1.0f, 0.0f, 0.0f, RED);
	yaxis = make_vertex(0.0f, 1.0f, 0.0f, GREEN);
	zaxis = make_vertex(0.0f, 0.0f, 1.0f, BLUE);
	mvp = ft_create_mvp(fdf_data, pos, rot, make_vec3_pos(scale, scale, scale));
	origin.pos = ft_transform_point(origin.pos, mvp);
	xaxis.pos = ft_transform_point(xaxis.pos, mvp);
	yaxis.pos = ft_transform_point(yaxis.pos, mvp);
	zaxis.pos = ft_transform_point(zaxis.pos, mvp);
	draw_line(fdf_data->f_buf, origin, xaxis);
	draw_line(fdf_data->f_buf, origin, yaxis);
	draw_line(fdf_data->f_buf, origin, zaxis);
}

void	ft_draw_info(t_fdf_data *fdf_data)
{
	mlx_string_put(fdf_data->mlx_ptr, fdf_data->win_ptr, 10, 10,
		ft_get_color(WHITE), fdf_data->view_state);
}
