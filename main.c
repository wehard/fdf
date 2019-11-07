/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/07 11:18:00 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "mlx.h"
#include "fdf.h"
#include "ft_get_next_line.h"

#define WHITE 0xFFFFFFF

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
	if (deltaY < 0)
	{
		yintercept = -1;
		deltaY = -deltaY;
	}
	D = 2 * deltaY - deltaX;
	y = p0.y;
	x = p0.x;
	while (x < p1.x)
	{
		mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, WHITE);
		if (D > 0)
		{
			y = y + yintercept;
			D = D - 2 * deltaX;
		}
		D = D + 2 * deltaY;
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
	mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, mouse_data->x, mouse_data->y, WHITE);

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
			vec_map[y * 19 + x] = make_vec3(x * 50 + xoff, y * 50 + yoff, ft_atoi(*points) * 50);
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
	t_vec3 vec_map[209];
	int	fd;
	int map_size;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		map_size = read_map_data(fd, vec_map);
		close(fd);
	}

	mlx_data = init("fdf");

	mlx_hook(mlx_data->win_ptr, 6, 0, on_mouse_move, mlx_data);
	mlx_hook(mlx_data->win_ptr, 2, 0, on_key_down, mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, mlx_data);
	//mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, p0.x, p0.y, 0xFFF0000);

	int x;
	int y;

	//draw_line(mlx_data, vec_map[0], vec_map[10]);

	y = 0;
	while (y < 11)
	{
		x = 0;
		while (x < 19)
		{
			t_vec3 p0 = vec_map[y * 19 + x];
			t_vec3 p1 = vec_map[y * 19 + x + 1];
			if(p1.z > 0)
				p1.y -= p1.z * 0.5;
			draw_line(mlx_data, p0, p1);
			mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, p0.x, p0.y, WHITE, "O");
			x++;
		}
		y++;
	}
	mlx_loop(mlx_data->mlx_ptr);
	free(mlx_data);
	return (0);
}
