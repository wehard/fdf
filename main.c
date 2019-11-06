/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/06 19:03:44 by wkorande         ###   ########.fr       */
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

void	draw_line(t_mlx_data *mlx_data, t_vec3 p0, t_vec3 p1)
{
	float x;
	float slope;
	float yintercept;
	float y;

	if (p1.z > 0)
			p1.y -= 5;

	x = p0.x;
	slope = (p1.y - p0.y) / (p1.x - p0.x);
	yintercept = p0.y;


	while (x < p1.x)
	{
		y = slope * x + yintercept;

		mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, x, y, WHITE);
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

t_vec3 *read_to_list(int fd)
{
	int y;
	int x;
	char	*line;
	char	**ps;

	t_vec3 *vec_map;
	vec_map = malloc(sizeof(t_vec3) * 20);

	t_list *new;
	t_vec3 vec3;
	t_list *p_lst;
	t_list **begin;
	begin = malloc(sizeof(t_list*));
	p_lst = *begin;
	y = 0;
	while (ft_get_next_line(fd, &line))
	{
		ps = ft_strsplit(line, ' ');
		x = 0;
		while (*ps)
		{
			vec3.x = x * 20;
			vec3.y = y * 20;
			vec3.z = ft_atoi(*ps) * 10;
			vec_map[y * 10 + x] = vec3;
			//new = ft_lstnew(&vec3, sizeof(vec3));
			//ft_lstappend(&p_lst, new);
			ps++;
			x++;
		}
		y++;
	}
	return (vec_map);
}



int	main(int argc, char const *argv[])
{
	t_mlx_data *mlx_data;
	t_vec3 *vec_map;

	if (argc == 2)
	{
		vec_map = read_to_list(open(argv[1], O_RDONLY));
	}


	mlx_data = init("fdf");

	mlx_key_hook(mlx_data->win_ptr, on_key_down, mlx_data);
	mlx_hook(mlx_data->win_ptr, 6, 0, on_mouse_move, mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, mlx_data);
	//mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, p0.x, p0.y, 0xFFF0000);
	/* t_vec3 p0;
	t_vec3 p1;

	p0.x = 10;
	p0.y = 10;
	p1.x = 490;
	p1.y = 10;
	draw_line(mlx_data, p0, p1); */
	int x;
	int y;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			draw_line(mlx_data, vec_map[y * 10 + x], vec_map[(y * 10) + x + 1]);
			//draw_line(mlx_data, vec_map[y * 10 + x], vec_map[((y+1) * 10) + x + 1]);
			//mlx_string_put(mlx_data->mlx_ptr, mlx_data->win_ptr, vec_map[y * 10 + x].x, vec_map[y * 10 + x].y, WHITE, "x");
			x++;
		}
		y++;
	}
	mlx_loop(mlx_data->mlx_ptr);
	return (0);
}
