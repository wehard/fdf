/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/10 19:04:33 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include "math.h"
#include "ft_get_next_line.h"

void		draw_axis(t_fdf_data *fdf_data, t_vec3 pos, t_vec3 rot, float scale)
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

	draw_line(fdf_data->f_buf, fdf_data->db, make_vertex(origin.x, origin.y, origin.z, RED), make_vertex(xaxis.x, xaxis.y, xaxis.z, RED));
	draw_line(fdf_data->f_buf, fdf_data->db, make_vertex(origin.x, origin.y, origin.z, GREEN), make_vertex(yaxis.x, yaxis.y, yaxis.z, GREEN));
	draw_line(fdf_data->f_buf, fdf_data->db, make_vertex(origin.x, origin.y, origin.z, BLUE), make_vertex(zaxis.x, zaxis.y, zaxis.z, BLUE));
}

int			discard_point(t_vec3 p)
{
	float zfar = -5.0f;
	float znear = -4.5f;
	if (p.x < -1.0 || p.x > 1.0f)
		return (1);
	if (p.y < -1.0 || p.y > 1.0f)
		return (1);
	//if (p.z < -1.0 || p.z > 1.0)
	//	return (1);
	return (0);
}

static void	ft_display_info(t_fdf_data *fdf_data)
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

void		draw_map(t_fdf_data *fdf_data)
{
	int x;
	int y;
	t_vertex v[4];

	t_mat4x4 m2w = create_trs_matrix(fdf_data->map->pos, fdf_data->map->rot, fdf_data->map->scale);
	t_mat4x4 w2v = multiply_matrix(m2w, create_view_matrix(fdf_data->camera.pos));
	t_mat4x4 mvp = multiply_matrix(w2v, *(fdf_data->m_proj));

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

			v[0].pos = multiply_matrix_vec3(v[0].pos, mvp);
			v[1].pos = multiply_matrix_vec3(v[1].pos, mvp);
			v[2].pos = multiply_matrix_vec3(v[2].pos, mvp);
			v[3].pos = multiply_matrix_vec3(v[3].pos, mvp);

			if (discard_point(v[0].pos) && discard_point(v[1].pos) && discard_point(v[2].pos) && discard_point(v[3].pos))
			{
				x++;
				continue;
			}

			v[0].pos = convert_to_screen_space(v[0].pos);
			v[1].pos = convert_to_screen_space(v[1].pos);
			v[2].pos = convert_to_screen_space(v[2].pos);
			v[3].pos = convert_to_screen_space(v[3].pos);
			draw_line(fdf_data->f_buf, fdf_data->db, v[0], v[1]);
			draw_line(fdf_data->f_buf, fdf_data->db, v[0], v[2]);
			if (x == fdf_data->map->w - 2)
				draw_line(fdf_data->f_buf, fdf_data->db, v[1], v[3]);
			if (y == fdf_data->map->h - 2)
				draw_line(fdf_data->f_buf, fdf_data->db, v[2], v[3]);
			x++;
		}
		y++;
	}
}

int		on_render(void *param)
{
	t_fdf_data *fdf_data;

	fdf_data = (t_fdf_data*)param;
	if (!fdf_data || !fdf_data->map)
		return (0);
	clear_frame_buffer(fdf_data->f_buf);
	draw_map(fdf_data);
	if (fdf_data->show_info)
		draw_axis(fdf_data, fdf_data->map->pos, fdf_data->map->rot, 10.0f);
	if (fdf_data->f_buf->img)
		mlx_put_image_to_window(fdf_data->mlx_ptr, fdf_data->win_ptr, fdf_data->f_buf->img, 0, 0);
	if (fdf_data->show_info)
		ft_display_info(fdf_data);
	return (0);
}

int		main(int argc, char const *argv[])
{
	t_fdf_data	*fdf_data;
	t_map		*map;
	int			fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 3 || !read_map_file(fd, &map, BLUE, WHITE))
		{
			close(fd);
			return (throw_error("error: map error"));
		}
	}
	else
		return (throw_error("usage: ./fdf mapfile"));
	if (!(fdf_data = init_fdf_data("fdf", map)))
		return (throw_error("fdf: failed to init!"));
	mlx_hook(fdf_data->win_ptr, 2, 0, on_key_down, (void*)fdf_data);
	mlx_loop_hook(fdf_data->mlx_ptr, on_render, (void*)fdf_data);
	mlx_loop(fdf_data->mlx_ptr);
	return (0);
}
