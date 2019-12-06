/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/06 14:08:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "mlx.h"
#include "fdf.h"
#include "matrix.h"
#include "point.h"
#include "math.h"
#include "ft_get_next_line.h"

t_mlx_data *init_mlx(char *title)
{
	t_mlx_data *mlx_data;
	float		znear;
	float		zfar;
	float		aspect;
	float		fov;
	float		ortho_size;

	mlx_data = (t_mlx_data*)malloc(sizeof(t_mlx_data));
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, WIN_W, WIN_H, title);
	mlx_data->f_buf = create_frame_buffer(mlx_data);
	mlx_data->db = create_depth_buffer(WIN_W, WIN_H);

	mlx_data->mouse_data.x = 0;
	mlx_data->mouse_data.y = 0;
	mlx_data->mouse_data.oldx = 0;
	mlx_data->mouse_data.oldy = 0;
	mlx_data->mouse_data.dx = 0;
	mlx_data->mouse_data.dy = 0;

	znear = 1.0f;
	zfar = 100.0f;
	aspect = (float)WIN_W / (float)WIN_H;
	ortho_size = 11.0f;
	fov = 30.0f;
	mlx_data->perspective_matrix = create_perspective_matrix(fov, aspect, znear, zfar);
	mlx_data->ortho_matrix = create_ortho_matrix(-ortho_size, ortho_size, aspect * -ortho_size, aspect * ortho_size, znear, zfar);

	mlx_data->m_proj = (t_mat4x4*)malloc(sizeof(t_mat4x4));
	*(mlx_data->m_proj) = mlx_data->ortho_matrix;

	mlx_data->camera.pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	mlx_data->camera.v_matrix = create_view_matrix(mlx_data->camera.pos);
	mlx_data->delta_time = 0.001f;
	return (mlx_data);
}

int	del_mlx(t_mlx_data *mlx_data)
{
	free(mlx_data->f_buf->d_addr);
	free(mlx_data->m_proj);
	free(mlx_data->db->data);
	free(mlx_data->db);

	mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->f_buf->img);
	free(mlx_data);
	return (1);
}

void	ft_set_ortho(t_mlx_data *mlx_data)
{
	*(mlx_data->m_proj) = mlx_data->ortho_matrix;
	mlx_data->v_map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	mlx_data->v_map->rot = make_vec3_rot(-35.264f, -45.0f, 0.0f);
	mlx_data->v_map->scale = make_vec3_rot(1.0f, 1.0f, 1.0f);

	//mlx_data->camera.pos = make_vec3_pos(0.0f, 0.0f, 20.0f);
}

void	ft_set_perspective(t_mlx_data *mlx_data)
{
	*(mlx_data->m_proj) = mlx_data->perspective_matrix;
	mlx_data->v_map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	mlx_data->v_map->rot = make_vec3_rot(-35.264f, -45.0f, 0.0f);
	mlx_data->v_map->scale = make_vec3_rot(1.0f, 1.0f, 1.0f);

	//mlx_data->camera.pos = make_vec3_pos(0.0f, 0.0f, 200.0f);
}

t_vec3 convert_to_screen_space(t_vec3 p)
{
	p.x += 1.0f;
	p.y += 1.0f;
	p.x *= 0.5f * (float)WIN_W;
	p.y *= 0.5f * (float)WIN_H;
	return (p);
}

void	draw_axis(t_mlx_data *mlx_data, t_vec3 pos, t_vec3 rot, float scale)
{
	t_vec3 origin = make_vec3_pos(0.0f, 0.0f, 0.0f);
	t_vec3 xaxis = make_vec3_pos(1.0f * scale, 0.0f, 0.0f);
	t_vec3 yaxis = make_vec3_pos(0.0f, 1.0f * scale, 0.0f);
	t_vec3 zaxis = make_vec3_pos(0.0f, 0.0f, 1.0f * scale);

	t_mat4x4 m2w = create_trs_matrix(pos, rot, make_vec3_rot(1.0f, 1.0f, 1.0f));
	t_mat4x4 w2v = multiply_matrix(m2w, create_view_matrix(mlx_data->camera.pos));
	t_mat4x4 mvp = multiply_matrix(w2v, *(mlx_data->m_proj));

	origin = multiply_matrix_vec3(origin, mvp);
	xaxis = multiply_matrix_vec3(xaxis, mvp);
	yaxis = multiply_matrix_vec3(yaxis, mvp);
	zaxis = multiply_matrix_vec3(zaxis, mvp);

	origin = convert_to_screen_space(origin);
	xaxis = convert_to_screen_space(xaxis);
	yaxis = convert_to_screen_space(yaxis);
	zaxis = convert_to_screen_space(zaxis);

	draw_line(mlx_data->f_buf, mlx_data->db, make_vertex(origin.x, origin.y, origin.z, RED), make_vertex(xaxis.x, xaxis.y, xaxis.z, RED));
	draw_line(mlx_data->f_buf, mlx_data->db, make_vertex(origin.x, origin.y, origin.z, GREEN), make_vertex(yaxis.x, yaxis.y, yaxis.z, GREEN));
	draw_line(mlx_data->f_buf, mlx_data->db, make_vertex(origin.x, origin.y, origin.z, BLUE), make_vertex(zaxis.x, zaxis.y, zaxis.z, BLUE));
}

int		discard_point(t_vec3 p)
{
	float zfar = -5.0f;
	float znear = -4.5f;
	if (p.x < -1.0 || p.x > 1.0f)
		return (1);
	if (p.y < -1.0 || p.y > 1.0f)
		return (1);
	//if (p.z < zfar || p.z > znear)
		//return (1);
	return (0);
}

static void	ft_display_info(t_mlx_data *mlx_data)
{
	char pos[50];
	char rot[50];
	char campos[50];

	sprintf(pos, "%.3f, %.3f, %.3f", mlx_data->v_map->pos.x, mlx_data->v_map->pos.y, mlx_data->v_map->pos.z);
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, 10, 10, ft_get_color(WHITE), "pos: ");
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, 50, 10, ft_get_color(WHITE), pos);

	sprintf(rot, "%.3f, %.3f, %.3f", mlx_data->v_map->rot.x, mlx_data->v_map->rot.y, mlx_data->v_map->rot.z);
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, 10, 25, ft_get_color(WHITE), "rot: ");
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, 50, 25, ft_get_color(WHITE), rot);

	sprintf(campos, "%.3f, %.3f, %.3f", mlx_data->camera.pos.x, mlx_data->camera.pos.y, mlx_data->camera.pos.z);
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, 970, 10, ft_get_color(WHITE), "cam pos: ");
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, 1060, 10, ft_get_color(WHITE), campos);
}


int on_render(void *param)
{
	t_mlx_data *mlx_data;
	mlx_data = (t_mlx_data*)param;
	if (!mlx_data || !mlx_data->v_map)
		return (0);

	//t_vec3 points[mlx_data->v_map->size];
	clear_frame_buffer(mlx_data->f_buf);
	clear_depth_buffer(mlx_data->db, 1000.0f);

	mlx_data->v_map->rot.x += (mlx_data->mouse_data.dy * 0.0001f);
	mlx_data->v_map->rot.y += -(mlx_data->mouse_data.dx * 0.0001f);

	t_mat4x4 m2w = create_trs_matrix(mlx_data->v_map->pos, mlx_data->v_map->rot, mlx_data->v_map->scale);
	t_mat4x4 w2v = multiply_matrix(m2w, create_view_matrix(mlx_data->camera.pos));
	t_mat4x4 mvp = multiply_matrix(w2v, *(mlx_data->m_proj));
	//transform_v_map(mlx_data, mlx_data->v_map, points);

	for (size_t y = 0; y < mlx_data->v_map->h - 1; y++)
	{
		for (size_t x = 0; x < mlx_data->v_map->w - 1; x++)
		{
			t_vec3 p0 = mlx_data->v_map->v[y * mlx_data->v_map->w + x];
			t_vec3 p1 = mlx_data->v_map->v[y * mlx_data->v_map->w + x + 1];
			t_vec3 p2 = mlx_data->v_map->v[(y + 1) * mlx_data->v_map->w + x];

			//
			t_rgba c0 = ft_lerp_rgba(BLUE, WHITE, ft_convert_range(p0.y, mlx_data->v_map->h_min, mlx_data->v_map->h_max, 0.0f, 1.0f));
			t_rgba c1 = ft_lerp_rgba(BLUE, WHITE, ft_convert_range(p1.y, mlx_data->v_map->h_min, mlx_data->v_map->h_max, 0.0f, 1.0f));
			t_rgba c2 = ft_lerp_rgba(BLUE, WHITE, ft_convert_range(p2.y, mlx_data->v_map->h_min, mlx_data->v_map->h_max, 0.0f, 1.0f));
			float p0y = p0.y;
			float p1y = p1.y;
			float p2y = p2.y;

			p0 = multiply_matrix_vec3(p0, mvp);
			p1 = multiply_matrix_vec3(p1, mvp);
			p2 = multiply_matrix_vec3(p2, mvp);

			if (discard_point(p0) || discard_point(p1) ||discard_point(p2))
				continue ;

			p0 = convert_to_screen_space(p0);
			p1 = convert_to_screen_space(p1);
			p2 = convert_to_screen_space(p2);
			draw_line(mlx_data->f_buf, mlx_data->db, make_vertex(p0.x, p0.y, p0.z, c0), make_vertex(p1.x, p1.y, p1.z, c1));
			draw_line(mlx_data->f_buf, mlx_data->db, make_vertex(p0.x, p0.y, p0.z, c0), make_vertex(p2.x, p2.y, p2.z, c2));
			//draw_line(mlx_data->f_buf, make_intvec2(p1.x, p1.y), make_intvec2(p2.x, p2.y));

		}
	}
	draw_axis(mlx_data, mlx_data->v_map->pos, mlx_data->v_map->rot, 10.0f);
	draw_axis(mlx_data, make_vec3_pos(0.0f, 0.0f, 0.0f), make_vec3_rot(0.0f, 0.0f, 0.0f), 1.0f);
	if (mlx_data->f_buf->img)
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->f_buf->img, 0, 0);

	ft_display_info(mlx_data);

	mlx_data->delta_time += 0.1f;
	return (0);
}


int	main(int argc, char const *argv[])
{
	t_mlx_data *mlx_data;
	t_v_map *map;
	int	fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 3)
		{
			close(fd);
			return (1);
		}
		if (!(read_map_data(fd, &map)))
		{
			ft_putstr("error: map data read failed!");
			close(fd);
			return (1);
		}
	}
	else
	{
		ft_putendl("enter map file as argument");
		return (1);
	}

	if (!(mlx_data = init_mlx("fdf")))
	{
		ft_putendl("mlx failed to init!");
		return (1);
	}

	mlx_data->v_map = map;

	ft_putstr("map width: ");
	ft_putnbr(mlx_data->v_map->w);
	ft_putchar('\n');
	ft_putstr("map height: ");
	ft_putnbr(mlx_data->v_map->h);
	ft_putchar('\n');

	center_map_origin(mlx_data->v_map);

	mlx_data->v_map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	mlx_data->v_map->rot = make_vec3_rot(-35.264f, -45.0f, 0.0f);
	mlx_data->v_map->scale = make_vec3_rot(1.0f, 1.0f, 1.0f);

	mlx_data->camera.pos = make_vec3_pos(0.0f, 0.0f, mlx_data->v_map->w);

	ft_print_matrix(mlx_data->perspective_matrix, 3);
	ft_print_matrix(mlx_data->ortho_matrix, 3);

	printf("mapmax: %i mapmin: %i\n", mlx_data->v_map->h_max, mlx_data->v_map->h_min);

	//mlx_key_hook(mlx_data->win_ptr, on_key_down, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 2, 0, on_key_down, (void*)mlx_data);
	mlx_mouse_hook(mlx_data->win_ptr,  mouse_event,(void*)mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, (void*)mlx_data);

	mlx_loop(mlx_data->mlx_ptr);
	if (!del_mlx(mlx_data))
		ft_putendl("mlx_del failed!");
	return (0);
}
