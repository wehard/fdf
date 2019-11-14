/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:28:18 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/14 12:50:50 by wkorande         ###   ########.fr       */
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
		mlx_data->v_map->rot = make_vec3_rot(0.0f, 0.0f, 0.0f);
		mlx_data->mouse_data.dy = 0;
		mlx_data->mouse_data.dy = 0;
	}
	if (key == KEY_W)
		mlx_data->v_map->rot.x += 0.1f;
	if (key == KEY_A)
		mlx_data->v_map->rot.y -= 0.1f;
	if (key == KEY_S)
		mlx_data->v_map->rot.x -= 0.1f;
	if (key == KEY_D)
		mlx_data->v_map->rot.y += 0.1f;
	if (key == KEY_Q)
		mlx_data->v_map->rot.z += 0.1f;
	if (key == KEY_E)
		mlx_data->v_map->rot.z -= 0.1f;
	if (key == KEY_1)
		*(mlx_data->m_proj) = mlx_data->perspective_matrix;
	if (key == KEY_2)
		*(mlx_data->m_proj) = mlx_data->ortho_matrix;
	if (key == KEY_R)
	{
		mlx_data->v_map->scale.x += 0.01f;
		mlx_data->v_map->scale.y += 0.01f;
		mlx_data->v_map->scale.z += 0.01f;
	}
	if (key == KEY_F)
	{
		mlx_data->v_map->scale.x -= 0.01f;
		mlx_data->v_map->scale.y -= 0.01f;
		mlx_data->v_map->scale.z -= 0.01f;
	}
	if (key == KEY_Z)
		mlx_data->v_map->pos.z += 1.0f;
	if (key == KEY_X)
		mlx_data->v_map->pos.z -= 1.0f;

	return (0);
}

int	mouse_event(int button, int x, int y, void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;

	mlx_data->mouse_data.oldx = mlx_data->mouse_data.x;
	mlx_data->mouse_data.oldy = mlx_data->mouse_data.y;

	mlx_data->mouse_data.x = x;
	mlx_data->mouse_data.y = y;

	mlx_data->mouse_data.dx = x - mlx_data->mouse_data.oldx;
	mlx_data->mouse_data.dy = y - mlx_data->mouse_data.oldy;

	return (0);
}
