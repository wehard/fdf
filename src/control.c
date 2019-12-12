/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:28:39 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/12 14:49:34 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_set_parallel(t_fdf_data *fdf_data)
{
	fdf_data->view_state = PARALLEL;
	*(fdf_data->m_proj) = fdf_data->ortho_matrix;
	fdf_data->map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	fdf_data->map->rot = make_vec3_rot(0.0f, 0.0f, 0.0f);
	fdf_data->map->scale = make_vec3_rot(1.0f, 1.0f, 1.0f);
}

void		ft_set_isometric(t_fdf_data *fdf_data)
{
	fdf_data->view_state = ISOMETRIC;
	*(fdf_data->m_proj) = fdf_data->ortho_matrix;
	fdf_data->map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	fdf_data->map->rot = make_vec3_rot(-35.264f, 45.0f, 0.0f);
	fdf_data->map->scale = make_vec3_rot(1.0f, 1.0f, 1.0f);
}

void		ft_set_perspective(t_fdf_data *fdf_data)
{
	fdf_data->view_state = PERSPECTIVE;
	*(fdf_data->m_proj) = fdf_data->perspective_matrix;
	fdf_data->map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	fdf_data->map->rot = make_vec3_rot(-45.0f, 0.0f, 0.0f);
	fdf_data->map->scale = make_vec3_rot(1.0f, 1.0f, 1.0f);
}

static void	handle_interface(int key, t_fdf_data *fdf_data)
{
	if (key == ESC)
		del_fdf_data(fdf_data);
	if (key == KEY_1)
		ft_set_isometric(fdf_data);
	if (key == KEY_2)
		ft_set_parallel(fdf_data);
	if (key == KEY_3)
		ft_set_perspective(fdf_data);
	if (key == KEY_I)
		fdf_data->show_info = !fdf_data->show_info;
}

int			on_key_down(int key, void *param)
{
	t_fdf_data	*fdf_data;
	float		rotation;

	fdf_data = (t_fdf_data*)param;
	if (fdf_data->view_state == ISOMETRIC)
		rotation = 90.0f;
	else
		rotation = 1.0f;
	handle_interface(key, fdf_data);
	if (key == KEY_W || key == KEY_A)
		key == KEY_W ? (fdf_data->map->rot.x += rotation) :
			(fdf_data->map->rot.y -= rotation);
	if (key == KEY_S || key == KEY_D)
		key == KEY_S ? (fdf_data->map->rot.x -= rotation) :
			(fdf_data->map->rot.y += rotation);
	if (key == KEY_Z || key == KEY_X)
		key == KEY_Z ? (fdf_data->camera.pos.z += 1.0f) :
			(fdf_data->camera.pos.z -= 1.0f);
	if (key == KEY_UP || key == KEY_DOWN)
		key == KEY_UP ? (fdf_data->camera.pos.y += 1.0f) :
			(fdf_data->camera.pos.y -= 1.0f);
	if (key == KEY_LEFT || key == KEY_RIGHT)
		key == KEY_LEFT ? (fdf_data->camera.pos.x -= 1.0f) :
			(fdf_data->camera.pos.x += 1.0f);
	return (0);
}
