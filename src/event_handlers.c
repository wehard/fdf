/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:28:18 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/10 16:57:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	on_key_down(int key, void *param)
{
	t_fdf_data *fdf_data;
	fdf_data = (t_fdf_data*)param;
	if (key == ESC)
		exit(EXIT_SUCCESS);
	if (key == KEY_1)
		ft_set_isometric(fdf_data);
	if (key == KEY_2)
		ft_set_parallel(fdf_data);
	if (key == KEY_3)
		ft_set_perspective(fdf_data);
	if (key == KEY_W)
		fdf_data->map->rot.x += 45.0f;
	if (key == KEY_A)
		fdf_data->map->rot.y -= 45.0f;
	if (key == KEY_S)
		fdf_data->map->rot.x -= 45.0f;
	if (key == KEY_D)
		fdf_data->map->rot.y += 45.0f;
	if (key == KEY_I)
		fdf_data->show_info = !fdf_data->show_info;
	if (key == KEY_Z || key == 122)
		fdf_data->camera.pos.z += 0.5f;
	if (key == KEY_X || key == 120)
		fdf_data->camera.pos.z -= 0.5f;
	if (key == KEY_UP)
		fdf_data->camera.pos.y += 1.0f;
	if (key == KEY_DOWN)
		fdf_data->camera.pos.y -= 1.0f;
	if (key == KEY_LEFT)
		fdf_data->camera.pos.x -= 1.0f;
	if (key == KEY_RIGHT)
		fdf_data->camera.pos.x += 1.0f;

	return (0);
}

int	mouse_event(int button, int x, int y, void *param)
{
	t_fdf_data *fdf_data;

	fdf_data = (t_fdf_data*)param;

	fdf_data->mouse_data.oldx = fdf_data->mouse_data.x;
	fdf_data->mouse_data.oldy = fdf_data->mouse_data.y;

	fdf_data->mouse_data.x = x;
	fdf_data->mouse_data.y = y;

	fdf_data->mouse_data.dx = (x - fdf_data->mouse_data.oldx) * 10.0f;
	fdf_data->mouse_data.dy = (y - fdf_data->mouse_data.oldy) * 10.0f;

	return (0);
}
