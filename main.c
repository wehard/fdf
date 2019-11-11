/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/11 12:23:31 by wkorande         ###   ########.fr       */
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

#define GREEN 0x00FF00
#define RED 0xFF0000
#define WHITE 0xFFFFFF

/*
** plotLineLow(x0,y0, x1,y1)
**   dx = x1 - x0
**   dy = y1 - y0
**   yi = 1
**   if dy < 0
**     yi = -1
**     dy = -dy
**   end if
**   D = 2*dy - dx
**   y = y0
**
**   for x from x0 to x1
**     plot(x,y)
**     if D > 0
**        y = y + yi
**        D = D - 2*dx
**     end if
**     D = D + 2*dy
*/

void	draw_line(t_mlx_data *mlx_data, t_vec3 p0, t_vec3 p1)
{
	float x;
	float y;
	float deltaX;
	float deltaY;
	float yintercept;
	float D;
	deltaX = p1.x - p0.x;
	deltaY = p1.y - p0.y;
	yintercept = 1;
	if (deltaY < 0.0f)
	{
		yintercept = -1.0f;
		deltaY = -deltaY;
	}
	D = 2.0f * deltaY - deltaX;
	y = p0.y;
	x = p0.x;
	while (x < p1.x)
	{
		mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, GREEN);
		if (D > 0.0f)
		{
			y = y + yintercept;
			D = D - 2.0f * deltaX;
		}
		D = D + 2.0f * deltaY;
		x++;
	}
}

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
		//free(line);
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

int on_render(void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;
	if (!mlx_data || !mlx_data->v_map)
		return (0);

	clear_frame_buffer(mlx_data->f_buf);
	int x;
	int y;

	float angle = mlx_data->delta_time * 0.4f;

	t_mat4x4 mat_rot_y = create_rotation_matrix_y(angle);
	t_mat4x4 mat_rot_z = create_rotation_matrix_z(-angle);
	t_mat4x4 s_matrix = create_scaling_matrix(make_vec3(1.6f, 1.6f, 0.2f));

	y = 0;
	while (y < mlx_data->v_map->h)
	{
		x = 0;
		while (x < mlx_data->v_map->w)
		{
			t_vec3 p = mlx_data->v_map->v[y * mlx_data->v_map->w + x];
			p.x -= mlx_data->v_map->w / 2;
			p.y -= mlx_data->v_map->h / 2;
			p = multiply_matrix_vec3(p, s_matrix);
			p = multiply_matrix_vec3(p, mat_rot_y);
			//p = multiply_matrix_vec3(p, mat_rot_z);
			p.z += 30.0f;
			p = multiply_matrix_vec3(p, *(mlx_data->m_proj));
			p.x += 1.0f;
			p.y += 1.0f;
			p.z += 10.0f;
			p.x *= 0.5f * (float)WIN_W;
			p.y *= 0.5f * (float)WIN_H;
			frame_buffer_set(mlx_data->f_buf, p.x, p.y, WHITE);
			x++;
		}
		y++;
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

	mlx_hook(mlx_data->win_ptr, 2, 0, on_key_down, mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, mlx_data);

	mlx_loop(mlx_data->mlx_ptr);
	free(mlx_data);
	return (0);
}
