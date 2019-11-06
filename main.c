/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/05 16:23:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//#include "libft.h"
#include "mlx.h"
#include "fdf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
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
	mouse_data = (t_mouse_data*)mlx_data;
	mlx_pixel_put(mlx_data->mlx_ptr, mlx_data->win_ptr, mouse_data->x, mouse_data->y, 0xFFFFFFF);
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

int	main(int argc, char const *argv[])
{
	t_mlx_data *mlx_data;

	mlx_data = init("fdf");

	mlx_key_hook(mlx_data->win_ptr, on_key_down, mlx_data);
	mlx_hook(mlx_data->win_ptr, 6, 0, on_mouse_move, mlx_data);
	mlx_loop_hook (mlx_data->mlx_ptr, on_render, mlx_data);

	mlx_loop(mlx_data->mlx_ptr);
	return (0);
}
