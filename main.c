/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/12 18:37:02 by wkorande         ###   ########.fr       */
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

int		on_key_down(int key, void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;

	if (key == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

t_mlx_data *init_mlx(char *title)
{
	t_mlx_data *mlx_data;
	float		znear;
	float		zfar;

	znear = 0.1f;
	zfar = 100.0f;
	mlx_data = (t_mlx_data*)malloc(sizeof(t_mlx_data));
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, WIN_W, WIN_H, title);
	mlx_data->f_buf = create_frame_buffer(mlx_data);
	//mlx_data->mouse_data = (t_mouse_data*)malloc(sizeof(t_mouse_data));
	//mlx_data->mouse_data->x = 0;
	//mlx_data->mouse_data->y = 0;
	//mlx_data->mouse_data->oldx = 0;
	//mlx_data->mouse_data->oldy = 0;
	mlx_data->m_proj = (t_mat4x4*)malloc(sizeof(t_mat4x4*));
	*(mlx_data->m_proj) = create_proj_matrix(znear, zfar, 90.0f, WIN_W, WIN_H);
	mlx_data->delta_time = 0.001f;
	return (mlx_data);
}

int	del_mlx(t_mlx_data *mlx_data)
{
	mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->f_buf->img);

	free(mlx_data->f_buf->d_addr);
	free(mlx_data->m_proj);
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

static void	center_origin(t_v_map *map)
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

	clear_frame_buffer(mlx_data->f_buf);
	int i;

	float angle = mlx_data->delta_time * 0.3f;

	t_mat4x4 mat_trans = create_translation_matrix(mlx_data->v_map->pos);
	t_mat4x4 mat_rot_y = create_rotation_matrix_y(angle);
	t_mat4x4 mat_rot_x = create_rotation_matrix_x(3.14f);
	t_mat4x4 mat_rot_z = create_rotation_matrix_z(-angle);
	t_mat4x4 s_matrix = create_scaling_matrix(make_vec3(1.0f, 1.0f, 0.1f));

	i = 0;
	while (i < mlx_data->v_map->size)
	{
			t_vec3 p0 = mlx_data->v_map->v[i];

			//p0 = multiply_matrix_vec3(p0, s_matrix);
			p0 = multiply_matrix_vec3(p0, mat_rot_x);
			p0 = multiply_matrix_vec3(p0, mat_rot_y);
			//p0 = transform_point(p0, make_vec3(1.0f, 1.0f, 10.0f), make_vec3(0.0f, 0.3f, 0.0f), make_vec3(1.0f, 1.0f, 1.0f));
			p0.z += mlx_data->v_map->w;
			p0.y += 5.0f;
			//p0 = multiply_matrix_vec3(p0, mat_trans); // TRANSLATE
			p0 = multiply_matrix_vec3(p0, *(mlx_data->m_proj));
			p0 = convert_to_screen_space(p0);

			frame_buffer_set(mlx_data->f_buf, p0.x, p0.y, WHITE);
			//draw_line(mlx_data->f_buf, p0, p1);
		i++;
	 }

	if (mlx_data->f_buf->img)
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->f_buf->img, 0, 0);
	mlx_data->delta_time += 0.1f;
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_mlx_data *mlx_data;
	int	fd;

	if (!(mlx_data = init_mlx("fdf")))
	{
		ft_putendl("mlx failed to init!");
		return (1);
	}

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 3)
		{
			close(fd);
			return (1);
		}
		if (!(read_map_data(fd, &mlx_data->v_map)))
		{
			ft_putstr("error: map data read failed!");
			close(fd);
			return (1);
		}
	}
	else
	{
		mlx_data->v_map = create_v_map(2, 4);
		mlx_data->v_map->v = make_unit_cube();
	}

	ft_putstr("map width: ");
	ft_putnbr(mlx_data->v_map->h);
	ft_putchar('\n');
	ft_putstr("map height: ");
	ft_putnbr(mlx_data->v_map->h);
	ft_putchar('\n');

	center_origin(mlx_data->v_map);
	mlx_data->v_map->pos = make_vec3(0.0f, 0.0f, 10.0f);

	mlx_hook(mlx_data->win_ptr, 2, 0, on_key_down, mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, mlx_data);

	mlx_loop(mlx_data->mlx_ptr);

	if (!del_mlx(mlx_data))
		ft_putendl("mlx_del failed!");
	return (0);
}
