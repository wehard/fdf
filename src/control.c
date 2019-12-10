/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:28:39 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/10 18:30:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_set_parallel(t_fdf_data *fdf_data)
{
	fdf_data->view_state = PARALLEL;
	*(fdf_data->m_proj) = fdf_data->ortho_matrix;
	fdf_data->map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	fdf_data->map->rot = make_vec3_rot(-45.0f, 0.0f, 0.0f);
	fdf_data->map->scale = make_vec3_rot(1.0f, 1.0f, 1.0f);
}

void		ft_set_isometric(t_fdf_data *fdf_data)
{
	fdf_data->view_state = ISOMETRIC;
	*(fdf_data->m_proj) = fdf_data->ortho_matrix;
	fdf_data->map->pos = make_vec3_pos(0.0f, 0.0f, 0.0f);
	fdf_data->map->rot = make_vec3_rot(-35.264f, -45.0f, 0.0f);
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
