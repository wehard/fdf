/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/07 21:56:09 by wkorande         ###   ########.fr       */
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

int	on_mouse_move(int x, int y, void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;
	mlx_data->mouse_data->x = x;
	mlx_data->mouse_data->y = y;
	return (0);
}

int on_render(void *param)
{
	t_mlx_data 	*mlx_data;
	t_mouse_data *mouse_data;
	mlx_data = (t_mlx_data*)param;
	mouse_data = (t_mouse_data*)mlx_data->mouse_data;
	//mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, mouse_data->x, mouse_data->y, WHITE);

	return (0);
}

t_mlx_data *init(char *title)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)malloc(sizeof(t_mlx_data));
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, WIN_W, WIN_H, title);
	mlx_data->mouse_data = (t_mouse_data*)malloc(sizeof(t_mouse_data));
	mlx_data->mouse_data->x = 0;
	mlx_data->mouse_data->y = 0;
	mlx_data->mouse_data->oldx = 0;
	mlx_data->mouse_data->oldy = 0;

	return (mlx_data);
}

int	read_map_data(int fd, t_vec3 *vec_map)
{
	int y;
	int x;
	char	*line;
	char	**points;
	int		size;
	t_vec3 vec3;
	int xoff = 100;
	int yoff = 100;

	size = 0;
	y = 0;
	while (ft_get_next_line(fd, &line))
	{
		points = ft_strsplit(line, ' ');
		x = 0;
		while (*points)
		{
			vec_map[y * 19 + x] = make_vec3(x, y, ft_atoi(*points));
			points++;
			x++;
			size++;
		}
		free(line);
		y++;
	}
	return (size);
}

int	main(int argc, char const *argv[])
{
	t_mlx_data *mlx_data;
	//t_vec3 vec_map[209];
	int	fd;
	//int map_size;

	float aspect = (float)WIN_W / (float)WIN_H;
	float zfar = 100.0f;
	float znear = 0.01f;

	t_mat4x4 m = create_proj_matrix(znear, zfar, 90.0f, WIN_W, WIN_H);

	t_vec3 ps[8] = {0};

	ps[0] = make_vec3(-0.5f, -0.5f, -0.5f);
	ps[1] = make_vec3(0.5f, -0.5f, -0.5f);
	ps[2] = make_vec3(-0.5f, -0.5f, 0.5f);
	ps[3] = make_vec3(0.5f, -0.5f, 0.5f);

	ps[4] = make_vec3(-0.5f, 0.5f, -0.5f);
	ps[5] = make_vec3(0.5f, 0.5f, -0.5f);
	ps[6] = make_vec3(-0.5f, 0.5f, -0.5f);
	ps[7] = make_vec3(0.5f, 0.5f, 0.5f);

	/* if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		map_size = read_map_data(fd, vec_map);
		close(fd);
	} */

	mlx_data = init("fdf");

	mlx_hook(mlx_data->win_ptr, 6, 0, on_mouse_move, mlx_data);
	mlx_hook(mlx_data->win_ptr, 2, 0, on_key_down, mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, mlx_data);
	//mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, p0.x, p0.y, 0xFFF0000);

	t_vec3 p0 = make_vec3(0.5f, 0.5f, 0.0f);
	t_vec3 p1 = make_vec3(-0.5f, -0.5f, 0.0f);

	p0 = multiply_matrix_vec3(p0, m);
	p1 = multiply_matrix_vec3(p1, m);

	p0.x += 1.0f;
	p0.y += 1.0f;

	p0.x *= 0.5f * (float)WIN_W;
	p0.y *= 0.5f * (float)WIN_H;

	p1.x += 1.0f;
	p1.y += 1.0f;

	p1.x *= 0.5f * (float)WIN_W;
	p1.y *= 0.5f * (float)WIN_H;

	//draw_line(mlx_data, vec_map[0], vec_map[10]);
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, p0.x, p0.y, GREEN, "X");
	mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, p1.x, p1.y, RED, "X");

	for (int i = 0; i < 8; i++)
	{
		ps[i].z = 2.0f;
		t_vec3 px = multiply_matrix_vec3(ps[i], m);
		px.x += 1.0f;
		px.y += 1.0f;
		px.x *= 0.5f * (float)WIN_W;
		px.y *= 0.5f * (float)WIN_H;
		mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, px.x, px.y, WHITE, "X");
	}


	//int x;
	//int y;
	/* y = 0;
	while (y < 11)
	{
		x = 0;
		while (x < 19)
		{
			t_vec3 p0 = multiply_matrix_vec3(vec_map[y * 19 + x], m);
			t_vec3 p1 = multiply_matrix_vec3(vec_map[y * 19 + x + 1], m);
			draw_line(mlx_data, p0, p1);
			//mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, p0.x, p0.y, WHITE, "O");
			x++;
		}
		y++;
	} */
	mlx_loop(mlx_data->mlx_ptr);
	free(mlx_data);
	return (0);
}
