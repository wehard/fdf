/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:04:16 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 14:11:52 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"
#include "mlx.h"

void	ft_draw_axis(t_fdf_data *fdf_data, t_vec3 pos, t_vec3 rot, float scale)
{
	t_vec3 origin = make_vec3_pos(0.0f, 0.0f, 0.0f);
	t_vec3 xaxis = make_vec3_pos(1.0f * scale, 0.0f, 0.0f);
	t_vec3 yaxis = make_vec3_pos(0.0f, 1.0f * scale, 0.0f);
	t_vec3 zaxis = make_vec3_pos(0.0f, 0.0f, 1.0f * scale);

	t_mat4x4 m2w = create_trs_matrix(pos, rot, make_vec3_rot(1.0f, 1.0f, 1.0f));
	t_mat4x4 w2v = multiply_matrix(m2w, create_view_matrix(fdf_data->camera.pos));
	t_mat4x4 mvp = multiply_matrix(w2v, *(fdf_data->m_proj));

	origin = multiply_matrix_vec3(origin, mvp);
	xaxis = multiply_matrix_vec3(xaxis, mvp);
	yaxis = multiply_matrix_vec3(yaxis, mvp);
	zaxis = multiply_matrix_vec3(zaxis, mvp);

	origin = convert_to_screen_space(origin);
	xaxis = convert_to_screen_space(xaxis);
	yaxis = convert_to_screen_space(yaxis);
	zaxis = convert_to_screen_space(zaxis);

	draw_line(fdf_data->f_buf, make_vertex(origin.x, origin.y, origin.z, RED), make_vertex(xaxis.x, xaxis.y, xaxis.z, RED));
	draw_line(fdf_data->f_buf, make_vertex(origin.x, origin.y, origin.z, GREEN), make_vertex(yaxis.x, yaxis.y, yaxis.z, GREEN));
	draw_line(fdf_data->f_buf, make_vertex(origin.x, origin.y, origin.z, BLUE), make_vertex(zaxis.x, zaxis.y, zaxis.z, BLUE));
}

void	ft_draw_info(t_fdf_data *fdf_data)
{
	char pos[50];
	char rot[50];
	char campos[50];

	mlx_string_put(fdf_data->mlx_ptr, fdf_data->win_ptr, 10, 10, ft_get_color(WHITE), fdf_data->view_state);

	sprintf(pos, "%.3f, %.3f, %.3f", fdf_data->map->pos.x, fdf_data->map->pos.y, fdf_data->map->pos.z);
	mlx_string_put(fdf_data->mlx_ptr, fdf_data->win_ptr, 10, 25, ft_get_color(WHITE), "pos: ");
	mlx_string_put(fdf_data->mlx_ptr, fdf_data->win_ptr, 50, 25, ft_get_color(WHITE), pos);

	sprintf(rot, "%.3f, %.3f, %.3f", fdf_data->map->rot.x, fdf_data->map->rot.y, fdf_data->map->rot.z);
	mlx_string_put(fdf_data->mlx_ptr, fdf_data->win_ptr, 10, 40, ft_get_color(WHITE), "rot: ");
	mlx_string_put(fdf_data->mlx_ptr, fdf_data->win_ptr, 50, 40, ft_get_color(WHITE), rot);

	sprintf(campos, "%.3f, %.3f, %.3f", fdf_data->camera.pos.x, fdf_data->camera.pos.y, fdf_data->camera.pos.z);
	mlx_string_put(fdf_data->mlx_ptr, fdf_data->win_ptr, 970, 10, ft_get_color(WHITE), "cam pos: ");
	mlx_string_put(fdf_data->mlx_ptr, fdf_data->win_ptr, 1060, 10, ft_get_color(WHITE), campos);
}
