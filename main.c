/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/02 22:32:15 by wkorande         ###   ########.fr       */
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

	mlx_data->mouse_data.x = 0;
	mlx_data->mouse_data.y = 0;
	mlx_data->mouse_data.oldx = 0;
	mlx_data->mouse_data.oldy = 0;
	mlx_data->mouse_data.dx = 0;
	mlx_data->mouse_data.dy = 0;

	znear = 0.1f;
	zfar = 10.0f;
	aspect = (float)WIN_W / (float)WIN_H;
	ortho_size = 11.0f;
	fov = 90.0f;
	mlx_data->perspective_matrix = create_proj_matrix(fov, aspect, znear, zfar);
	mlx_data->ortho_matrix = create_ortho_matrix(-ortho_size, ortho_size, aspect * -ortho_size, aspect * ortho_size, znear, zfar); //create_ortho_matrix_2((float)WIN_W, (float)WIN_H, 1.0f, -1.0f); //

	mlx_data->m_proj = (t_mat4x4*)malloc(sizeof(t_mat4x4));
	*(mlx_data->m_proj) = mlx_data->perspective_matrix;

	mlx_data->camera.pos = make_vec3_pos(0.0f, 0.0f, 150.0f);
	mlx_data->camera.v_matrix = create_view_matrix(mlx_data->camera.pos);
	mlx_data->delta_time = 0.001f;
	return (mlx_data);
}

int	del_mlx(t_mlx_data *mlx_data)
{
	free(mlx_data->f_buf->d_addr);
	free(mlx_data->m_proj);

	mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->f_buf->img);
	free(mlx_data);
	return (1);
}

t_vec3 convert_to_screen_space(t_vec3 p)
{
	p.x += 1.0f;
	p.y += 1.0f;
	p.x *= 0.5f * (float)WIN_W;
	p.y *= 0.5f * (float)WIN_H;
	return (p);
}

static void	center_map_origin(t_v_map *map)
{
	int x;
	int y;
	double half_w;
	double half_h;

	half_w = (float)map->w * 0.5f;
	half_h = (float)map->h * 0.5f;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			map->v[y * map->w + x].x -= half_w;
			map->v[y * map->w + x].z -= half_h;
			x++;
		}
		y++;
	}
}

static void transform_v_map(t_mlx_data *mlx_data, t_v_map *v_map, t_vec3 *out)
{
	int x;
	int y;

	t_mat4x4 m2w = create_trs_matrix2(v_map->pos, v_map->rot, v_map->scale);
	t_mat4x4 w2v = multiply_matrix(m2w, create_view_matrix(mlx_data->camera.pos));
	t_mat4x4 mvp = multiply_matrix(w2v, *(mlx_data->m_proj));

	y = 0;
	while (y < v_map->h)
	{
		x = 0;
		while (x < v_map->w)
		{
			t_vec3 p0 = v_map->v[y * v_map->w + x];
			p0 = multiply_matrix_vec3(p0, mvp);
			p0 = convert_to_screen_space(p0);
			out[y * v_map->w + x] = p0;
			x++;
		}
		y++;
	}
}

void	draw_axis(t_mlx_data *mlx_data, t_vec3 pos, t_vec3 rot, float scale)
{
	t_vec3 origin = make_vec3_pos(0.0f, 0.0f, 0.0f);
	t_vec3 xaxis = make_vec3_pos(1.0f * scale, 0.0f, 0.0f);
	t_vec3 yaxis = make_vec3_pos(0.0f, 1.0f * scale, 0.0f);
	t_vec3 zaxis = make_vec3_pos(0.0f, 0.0f, 1.0f * scale);

	t_mat4x4 m2w = create_trs_matrix2(pos, rot, make_vec3_pos(1.0f, 1.0f, 1.0f));
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

	draw_line(mlx_data->f_buf, make_intvec2(origin.x, origin.y), make_intvec2(xaxis.x, xaxis.y), RED);
	draw_line(mlx_data->f_buf, make_intvec2(origin.x, origin.y), make_intvec2(yaxis.x, yaxis.y), GREEN);
	draw_line(mlx_data->f_buf, make_intvec2(origin.x, origin.y), make_intvec2(zaxis.x, zaxis.y), BLUE);
}

int on_render(void *param)
{
	t_mlx_data *mlx_data;
	mlx_data = (t_mlx_data*)param;
	if (!mlx_data || !mlx_data->v_map)
		return (0);

	t_vec3 points[mlx_data->v_map->size];
	clear_frame_buffer(mlx_data->f_buf);

	mlx_data->v_map->rot.x += (mlx_data->mouse_data.dy * 0.0001f);
	mlx_data->v_map->rot.y += -(mlx_data->mouse_data.dx * 0.0001f);

	transform_v_map(mlx_data, mlx_data->v_map, points);

	for (size_t y = 0; y < mlx_data->v_map->h - 1; y++)
	{
		for (size_t x = 0; x < mlx_data->v_map->w - 1; x++)
		{
			t_vec3 p0 = points[y * mlx_data->v_map->w + x];
			t_vec3 p1 = points[y * mlx_data->v_map->w + x + 1];
			t_vec3 p2 = points[(y + 1) * mlx_data->v_map->w + x];

			draw_line(mlx_data->f_buf, make_intvec2(p0.x, p0.y), make_intvec2(p1.x, p1.y), WHITE);
			draw_line(mlx_data->f_buf, make_intvec2(p0.x, p0.y), make_intvec2(p2.x, p2.y), WHITE);
			//draw_line(mlx_data->f_buf, make_intvec2(p1.x, p1.y), make_intvec2(p2.x, p2.y));

		}
	}
	draw_axis(mlx_data, mlx_data->v_map->pos, mlx_data->v_map->rot, 20.0f);
	draw_axis(mlx_data, make_vec3_pos(0.0f, 0.0f, 0.0f), make_vec3_rot(0.0f, 0.0f, 0.0f), 5.0f);
	if (mlx_data->f_buf->img)
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->f_buf->img, 0, 0);
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
	ft_putnbr(mlx_data->v_map->h);
	ft_putchar('\n');
	ft_putstr("map height: ");
	ft_putnbr(mlx_data->v_map->h);
	ft_putchar('\n');

	center_map_origin(mlx_data->v_map);
	// degrees × π / 180°
	mlx_data->v_map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	mlx_data->v_map->rot = make_vec3_rot(0.0f, 0.0f, 0.0f);
	mlx_data->v_map->scale = make_vec3_rot(1.0f, 1.0f, 1.0f);


	t_vec3 t = make_vec3_pos(10.0f, 10.0f, 10.0f);
	t_mat4x4 m = create_translation_matrix(make_vec3_pos(10.0f, 0.0f, 0.0f));
	ft_print_matrix(m, 3);

	t = multiply_matrix_vec3_2(t, m);
	ft_print_vec3(t, 3);

	mlx_key_hook(mlx_data->win_ptr, on_key_down, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 2, 0, on_key_down, (void*)mlx_data);
	mlx_mouse_hook(mlx_data->win_ptr,  mouse_event,(void*)mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, (void*)mlx_data);

	mlx_loop(mlx_data->mlx_ptr);
	if (!del_mlx(mlx_data))
		ft_putendl("mlx_del failed!");
	return (0);
}
