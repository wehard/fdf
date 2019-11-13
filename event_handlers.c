/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:28:18 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/13 13:17:29 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	on_key_down(int key, void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;
	ft_putnbr(key);
	ft_putchar('\n');
	if (key == ESC)
		exit(EXIT_SUCCESS);
	if (key == SPACE)
	{
		mlx_data->v_map->rot = make_vec3(0.0f, 0.0f, 0.0f);
		mlx_data->mouse_data->dy = 0;
		mlx_data->mouse_data->dy = 0;
	}
	return (0);
}

int	mouse_event(int button, int x, int y, void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;

	mlx_data->mouse_data->oldx = mlx_data->mouse_data->x;
	mlx_data->mouse_data->oldy = mlx_data->mouse_data->y;

	mlx_data->mouse_data->x = x;
	mlx_data->mouse_data->y = y;

	mlx_data->mouse_data->dx = x - mlx_data->mouse_data->oldx;
	mlx_data->mouse_data->dy = y - mlx_data->mouse_data->oldy;

	return (0);
}
