/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/11 17:51:34 by wkorande         ###   ########.fr       */
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

t_mlx_data *init(char *title)
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

static t_v_map *create_v_map(int w, int h)
{
	t_v_map *v_map;
	int		size;

	size = w * h;
	if (!(v_map = (t_v_map*)malloc(sizeof(t_v_map))))
		return (NULL);
	v_map->size = size;
	v_map->w = w;
	v_map->h = h;
	if (!(v_map->v = (t_vec3*)malloc(sizeof(t_vec3) * size)))
		return (NULL);
	ft_bzero(v_map->v, size);
	return (v_map);
}

t_v_map	*read_map_data(int fd)
{
	t_v_map *v_map;
	int y;
	int x;
	char	*line;
	char	**points;
	int		size;
	t_vec3 vec3;
	int xoff = 100;
	int yoff = 100;

	if (!(v_map = create_v_map(19, 11)))
		return (NULL);

	size = 0;
	y = 0;
	while (ft_get_next_line(fd, &line))
	{
		points = ft_strsplit(line, ' ');
		x = 0;
		while (*points)
		{
			v_map->v[y * v_map->w + x] = make_vec3(x, y, -ft_atoi(*points));
			points++;
			x++;
			size++;
		}
		free(line);
		y++;
	}
	return (v_map);
}

static t_vec3 *make_unit_cube()
{
	t_vec3 *ps;

	ps = (t_vec3*)malloc(sizeof(t_vec3) * 8);
	ps[0] = make_vec3(-0.5f, -0.5f, -0.5f);
	ps[1] = make_vec3(0.5f, -0.5f, -0.5f);
	ps[2] = make_vec3(-0.5f, 0.5f, -0.5f);
	ps[3] = make_vec3(0.5f, 0.5f, -0.5f);
	ps[4] = make_vec3(-0.5f, -0.5f, 0.5f);
	ps[5] = make_vec3(0.5f, -0.5f, 0.5f);
	ps[6] = make_vec3(-0.5f, 0.5f, 0.5f);
	ps[7] = make_vec3(0.5f, 0.5f, 0.5f);
	return (ps);
}

t_vec3 convert_to_screen_space(t_vec3 p)
{
	p.x += 1.0f;
	p.y += 1.0f;
	p.x *= 0.5f * (float)WIN_W;
	p.y *= 0.5f * (float)WIN_H;
	return (p);
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

	//t_mat4x4 mat_trans = create_translation_matrix(make_vec3(1.0f, 1.0f, 3.0f));
	t_mat4x4 mat_rot_y = create_rotation_matrix_y(angle);
	//t_mat4x4 mat_rot_z = create_rotation_matrix_z(-angle);
	t_mat4x4 s_matrix = create_scaling_matrix(make_vec3(1.0f, 1.0f, 0.1f));

	i = 0;
	while (i < mlx_data->v_map->size)
	{
			t_vec3 p0 = mlx_data->v_map->v[i];
			p0.x -= mlx_data->v_map->w / 2;
			p0.y -= mlx_data->v_map->h / 2;
			p0 = multiply_matrix_vec3(p0, s_matrix);
			p0 = multiply_matrix_vec3(p0, mat_rot_y);
			//p0 = multiply_matrix_vec3(p0, mat_rot_z);
			p0.z += 20.0f;
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

	mlx_data = init("fdf");


	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 3)
		{
			close(fd);
			return (1);
		}
		if (!(mlx_data->v_map = read_map_data(fd)))
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


	mlx_hook(mlx_data->win_ptr, 2, 0, on_key_down, mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, mlx_data);

	mlx_loop(mlx_data->mlx_ptr);
	free(mlx_data);
	return (0);
}
