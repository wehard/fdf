/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/19 13:21:27 by wkorande         ###   ########.fr       */
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
	mlx_data->perspective_matrix = create_proj_matrix(znear, zfar, fov, aspect);
	mlx_data->ortho_matrix = create_ortho_matrix(-ortho_size, ortho_size, aspect * -ortho_size, aspect * ortho_size, 1.0f, -1.0f); //create_ortho_matrix_2((float)WIN_W, (float)WIN_H, 1.0f, -1.0f); //

	mlx_data->m_proj = (t_mat4x4*)malloc(sizeof(t_mat4x4));
	*(mlx_data->m_proj) = mlx_data->perspective_matrix;

	mlx_data->camera.pos = make_vec3_rot(0.0f, 0.0f, -50.0f);
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
			map->v[y * map->w + x].y -= half_h;
			x++;
		}
		y++;
	}
}

int on_render(void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;
	if (!mlx_data || !mlx_data->v_map)
		return (0);

	// ft_putstr("dx: ");
	// ft_putnbr(mlx_data->mouse_data->dx);
	// ft_putstr(" dy: ");
	// ft_putnbr(mlx_data->mouse_data->dy);
	// ft_putchar('\n');

	clear_frame_buffer(mlx_data->f_buf);
	int i;

	mlx_data->v_map->rot.x += (mlx_data->mouse_data.dy * 0.0001f);
	mlx_data->v_map->rot.y += -(mlx_data->mouse_data.dx * 0.0001f);

	t_mat4x4 mat_rot_y = create_rotation_matrix_y(mlx_data->v_map->rot.y);
	t_mat4x4 mat_rot_x = create_rotation_matrix_x(mlx_data->v_map->rot.x);
	t_mat4x4 mat_rot_z = create_rotation_matrix_z(mlx_data->v_map->rot.z);
	t_mat4x4 mat_scale = create_scaling_matrix(mlx_data->v_map->scale);
	t_mat4x4 mat_trans = create_translation_matrix(mlx_data->v_map->pos);
	t_mat4x4 mat_view = create_view_matrix(mlx_data->camera.pos);


	for (size_t y = 0; y < mlx_data->v_map->h; y++)
	{
		for (size_t x = 0; x < mlx_data->v_map->w - 1; x++)
		{
			t_vec3 p0 = mlx_data->v_map->v[y * mlx_data->v_map->w + x];
			p0 = multiply_matrix_vec3_test(p0, mat_rot_x);
			p0 = multiply_matrix_vec3_test(p0, mat_rot_y);
			p0 = multiply_matrix_vec3_test(p0, mat_rot_z);
			p0 = multiply_matrix_vec3_test(p0, mat_scale);
			p0 = multiply_matrix_vec3_test(p0, mat_trans);
			p0 = multiply_matrix_vec3(p0, mat_view);
			p0 = multiply_matrix_vec3_test(p0, *(mlx_data->m_proj));
			p0 = convert_to_screen_space(p0);

			t_vec3 p1 = mlx_data->v_map->v[y * mlx_data->v_map->w + x + 1];
			p1 = multiply_matrix_vec3_test(p1, mat_rot_x);
			p1 = multiply_matrix_vec3_test(p1, mat_rot_y);
			p1 = multiply_matrix_vec3_test(p1, mat_rot_z);
			p1 = multiply_matrix_vec3_test(p1, mat_scale);
			p1 = multiply_matrix_vec3_test(p1, mat_trans);
			p1 = multiply_matrix_vec3(p1, mat_view);
			p1 = multiply_matrix_vec3_test(p1, *(mlx_data->m_proj));
			p1 = convert_to_screen_space(p1);

			t_intvec2 i0;
			i0.x = p0.x;
			i0.y = p0.y;
			t_intvec2 i1;
			i1.x = p1.x;
			i1.y = p1.y;
			draw_line(mlx_data->f_buf, i0, i1);
			//frame_buffer_set(mlx_data->f_buf, p0.x, p0.y, WHITE);
		}
	}

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
	mlx_data->v_map->rot = make_vec3_pos(0.0f, 0.0f, 0.0f); //45.0f * (M_PI / 180.0f)
	mlx_data->v_map->scale = make_vec3_rot(1.0f, 1.0f, 1.0f);

	mlx_hook(mlx_data->win_ptr, 2, 0, on_key_down, (void*)mlx_data);
	mlx_mouse_hook(mlx_data->win_ptr,  mouse_event,(void*)mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, (void*)mlx_data);

	mlx_loop(mlx_data->mlx_ptr);
	if (!del_mlx(mlx_data))
		ft_putendl("mlx_del failed!");
	return (0);
}
